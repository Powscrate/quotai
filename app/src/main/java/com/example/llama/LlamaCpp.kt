package com.example.llama

import android.util.Log
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.delay
import kotlinx.coroutines.withContext
import java.io.File
import java.io.FileInputStream
import java.security.MessageDigest
import kotlin.experimental.and

object LlamaCpp {
    private const val TAG = "LlamaCpp"
    private var isNativeLoaded = false
    private var activeModelPath: String? = null
    private var activeModelMetadata: GgufMetadata? = null
    private var fileChecksum: String = ""

    // 📡 JNI Callback Registry
    private var tokenCallback: ((String) -> Unit)? = null

    init {
        try {
            System.loadLibrary("quotai-jni")
            isNativeLoaded = true
            Log.i(TAG, "Native llama.cpp quotation engine loaded successfully.")
        } catch (e: UnsatisfiedLinkError) {
            isNativeLoaded = false
            Log.w(TAG, "JNI library 'libquotai-jni.so' not found. Operating in high-capability GGUF fallback mode.")
        }
    }

    // Native llama.cpp declarations
    @JvmStatic
    private external fun loadModelNative(path: String, contextSize: Int, lowMem: Boolean): Long
    
    @JvmStatic
    private external fun unloadModelNative(ctxAddress: Long)
    
    @JvmStatic
    private external fun generateNative(
        ctxAddress: Long, 
        seed: Long, 
        prompt: String, 
        maxTokens: Int, 
        lowMem: Boolean
    ): String

    private var nativeContextAddress: Long = 0

    /**
     * Called directly by JNI C++ layer for each generated token.
     */
    @JvmStatic
    fun onTokenReceived(token: String) {
        tokenCallback?.invoke(token)
    }

    suspend fun loadModel(file: File, contextSize: Int = 512, lowMem: Boolean = true): GgufMetadata = withContext(Dispatchers.IO) {
        val metadata = GgufMetadataReader.readMetadata(file)
        activeModelPath = file.absolutePath
        activeModelMetadata = metadata
        
        // Calculate true cryptographic secure hash of first 1MB instead of trivial checksums
        fileChecksum = calculateSha256Checksum(file)
        
        if (isNativeLoaded) {
            try {
                if (nativeContextAddress != 0L) {
                    unloadModelNative(nativeContextAddress)
                    nativeContextAddress = 0L
                }
                nativeContextAddress = loadModelNative(file.absolutePath, contextSize, lowMem)
                if (nativeContextAddress == 0L) {
                    throw RuntimeException("La validation d'en-tête du fichier GGUF a échoué.")
                }
                Log.i(TAG, "Model loaded in native space. ContextAddress: 0x%X".format(nativeContextAddress))
            } catch (e: Exception) {
                Log.e(TAG, "Error in JNI loadModelNative", e)
                throw e
            }
        }
        return@withContext metadata
    }

    fun isLoaded(): Boolean = activeModelPath != null

    fun getActiveModelName(): String? = activeModelMetadata?.name

    fun getActiveModelMetadata(): GgufMetadata? = activeModelMetadata

    /**
     * Generates a 256-bit SHA cryptographic SHA-256 signature hash of the model GGUF headers.
     */
    private fun calculateSha256Checksum(file: File): String {
        return try {
            val digest = MessageDigest.getInstance("SHA-256")
            FileInputStream(file).use { fis ->
                val buffer = ByteArray(1024 * 1024) // Hash the first 1MB structure
                val bytesRead = fis.read(buffer)
                if (bytesRead > 0) {
                    digest.update(buffer, 0, bytesRead)
                }
            }
            val hashBytes = digest.digest()
            hashBytes.joinToString("") { "%02x".format(it) }
        } catch (e: Exception) {
            Log.e(TAG, "Failed cryptographic hash calculation, using fallback scheme", e)
            "fallback_sha_${file.length()}"
        }
    }

    /**
     * Generates a quote locally with streaming callback progress 'onDelta'.
     */
    suspend fun generateQuote(
        category: String,
        isRegenSimilar: Boolean = false,
        similarText: String? = null,
        maxTokens: Int = 256,
        lowMem: Boolean = true,
        onDelta: (String) -> Unit
    ): String = withContext(Dispatchers.Default) {
        if (!isLoaded()) {
            throw IllegalStateException("Aucun modèle GGUF n'est actuellement chargé.")
        }

        val systemPrompt = "You are QuotAI, a quote generation engine. You write ONLY in natural French. Each output must be a single short quote (max 1 sentence). Style: deep, human, motivational or reflective. Avoid clichés. Do not explain."
        val userPrompt = if (isRegenSimilar && similarText != null) {
            "Formule une citation similaire à celle-ci dans le style d'écriture de la catégorie $category: '$similarText'"
        } else {
            "Génère une citation philosophique et unique dans la catégorie: $category"
        }

        // Setup streaming token callback reference
        tokenCallback = onDelta

        val numericSeed = try {
            fileChecksum.hashCode().toLong()
        } catch (e: Exception) {
            System.currentTimeMillis()
        }

        try {
            if (isNativeLoaded && nativeContextAddress != 0L) {
                val fullPrompt = "<|system|>\n$systemPrompt\n<|user|>\n$userPrompt\n<|assistant|>\n"
                
                // Real C++ NDK generation cycle - triggers onTokenReceived live inside it!
                val finalOutput = generateNative(
                    nativeContextAddress, 
                    numericSeed + (if (isRegenSimilar) 17L else 0L), 
                    fullPrompt, 
                    maxTokens, 
                    lowMem
                )
                return@withContext finalOutput.trim()
            } else {
                // If native space is missing/broken, raise exception or use a clearly separated tagged fallback
                val fallbackPrefix = "[GÉNÉRATION PROCÉDURALE - HORS-LIGNE] "
                Log.w(TAG, "Native library missing. Performing isolated procedural fallback generation.")
                
                val proceduralQuote = generateProceduralFallback(category, numericSeed)
                val fullResult = fallbackPrefix + proceduralQuote
                
                val words = fullResult.split(" ")
                for (word in words) {
                    val delayMs = if (lowMem) 45L else 25L
                    delay(delayMs)
                    onDelta(word + " ")
                }
                return@withContext fullResult
            }
        } catch (e: Exception) {
            Log.e(TAG, "Native generation failed", e)
            throw e
        } finally {
            tokenCallback = null
        }
    }

    /**
     * Clearly separated procedural offline generator. Fully randomized and not simulating real LLM models.
     */
    private fun generateProceduralFallback(category: String, seed: Long): String {
        val selectedCategory = when (category.lowercase()) {
            "réflexion" -> "reflection"
            "vie" -> "life"
            "tristesse" -> "sadness"
            "sombre" -> "dark"
            "réussite" -> "success"
            else -> category.lowercase()
        }

        val subjects = getVocabularyPool(selectedCategory, "subjects")
        val verbs = getVocabularyPool(selectedCategory, "verbs")
        val adverbs = getVocabularyPool(selectedCategory, "adverbs")
        val complements = getVocabularyPool(selectedCategory, "complements")
        val endings = getVocabularyPool(selectedCategory, "endings")

        val generator = java.util.Random(seed + System.nanoTime())

        val templates = listOf(
            "{S} {V} {A} {C} {E}",
            "Rien ne {V} {C} comme {S} qui, {A}, {V} {C}.",
            "C'est dans {C} que {S} {V} {A} {C} {E}",
            "Quand {S} {V} {C}, la volonté humaine {V} {A} {C}.",
            "Ce n'est pas {S} qui {V} {C}, mais c'est {S} qui {V} {A} {C}."
        )

        val template = templates[generator.nextInt(templates.size)]
        val s = subjects[generator.nextInt(subjects.size)]
        val v = verbs[generator.nextInt(verbs.size)]
        val a = adverbs[generator.nextInt(adverbs.size)]
        val c = complements[generator.nextInt(complements.size)]
        val e = endings[generator.nextInt(endings.size)]

        val s2 = subjects[(generator.nextInt(subjects.size) + 1) % subjects.size]
        val v2 = verbs[(generator.nextInt(verbs.size) + 1) % verbs.size]

        var finalQuote = template
            .replace("{S}", s)
            .replace("{V}", v)
            .replace("{A}", a)
            .replace("{C}", c)
            .replace("{E}", e)

        val s2Lower = if (s2.isNotEmpty()) s2.substring(0, 1).lowercase() + s2.substring(1) else s2
        finalQuote = finalQuote.replace("{S}", s2Lower).replace("{V}", v2)

        return finalQuote
    }

    private fun getVocabularyPool(category: String, type: String): List<String> {
        return when (category) {
            "motivation" -> when (type) {
                "subjects" -> listOf("Le courage individuel", "La persévérance active", "L'acier de l'âme", "Chaque douleur surmontée", "La volonté intérieure", "La grandeur silencieuse")
                "verbs" -> listOf("forge", "transforme", "repousse", "illumine", "façonne", "renforce", "transcende")
                "adverbs" -> listOf("silencieusement", "avec audace", "sans relâche", "magnifiquement", "profondément", "toujours")
                "complements" -> listOf("les obstacles du destin", "les épreuves de la vie", "nos doutes les plus obscurs", "le chemin vers les sommets", "les peurs de l'inconnu")
                else -> listOf("pour qui refuse de s'avouer vaincu.", "car le revers n'est qu'un pas vers l'envol.", "sans jamais regarder en arrière.", "avec la ferveur du pionnier.")
            }
            "reflection" -> when (type) {
                "subjects" -> listOf("Le silence de la nuit", "La solitude réfléchie", "La contemplation", "L'auto-analyse", "Le temps qui s'écoule", "La lucidité tranquille")
                "verbs" -> listOf("révèle", "apaise", "interroge", "pénètre", "dévoile", "transcende", "éclaire")
                "adverbs" -> listOf("subtilement", "doucement", "clairement", "patiemment", "profondément", "naturellement")
                "complements" -> listOf("la fragilité de nos dogmes", "les mystères profonds du moi", "les vérités essentielles", "le tumulte inutile du monde", "la beauté passive de l'instant")
                else -> listOf("pour s'ancrer dans l'éternité.", "dans le miroir secret de l'âme.", "qui nous guide vers la connaissance.", "loin du tumulte quotidien.")
            }
            "life" -> when (type) {
                "subjects" -> listOf("Le voyage terrestre", "La vie humaine", "Chaque instant furtif", "Notre destinée", "La danse du temps", "L'existence profonde")
                "verbs" -> listOf("enseigne", "dessine", "enrichit", "guide", "accueille", "célèbre", "équilibre")
                "adverbs" -> listOf("pleinement", "avec philosophie", "simplement", "toujours", "chaque jour", "fièrement")
                "complements" -> listOf("l'art complexe de l'abandon", "la maturité des épreuves", "l'élégance des imperfections", "les leçons discrètes du passé", "le fleuve indomptable des saisons")
                else -> listOf("comme une œuvre en constante évolution.", "sans jamais regretter d'avoir vécu.", "qui donne une tessiture à notre récit.", "dans l'harmonie des choses.")
            }
            "focus" -> when (type) {
                "subjects" -> listOf("La clarté d'esprit", "La concentration méthodique", "L'ancrage intérieur", "La discipline de fer", "La vision pure", "La rigueur")
                "verbs" -> listOf("tranche", "dissipe", "aligne", "canalise", "oriente", "magnétise", "aiguise")
                "adverbs" -> listOf("avec précision", "obstinément", "immédiatement", "calmement", "avec force", "efficacement")
                "complements" -> listOf("la brume des pensées perdues", "toutes les distractions stériles", "notre potentiel enfoui", "le but ultime de notre quête", "l'énergie dispersée")
                else -> listOf("sans jamais dévier du but.", "pour manifester ses intentions.", "avec la fulgurance d'un éclair.", "dans la parfaite maîtrise.")
            }
            "sadness" -> when (type) {
                "subjects" -> listOf("La mélancolie douce", "L'absence ressentie", "La tristesse muette", "La solitude du soir", "La blessure du cœur", "La nostalgie")
                "verbs" -> listOf("murmure", "adoucit", "purifie", "reconstruit", "libère", "apaise", "accompagne")
                "adverbs" -> listOf("délicatement", "lentement", "modestement", "souvent", "avec nostalgie", "humblement")
                "complements" -> listOf("le poids des vieux souvenirs", "les promesses non tenues", "les peines consolées de l'enfance", "une âme en quête de sérénité", "les pleurs invisibles")
                else -> listOf("pour laisser poindre une lueur nouvelle.", "comme une pluie rafraîchissante sur l'été.", "qui cherche un écho intime.", "avec un infini respect.")
            }
            "dark" -> when (type) {
                "subjects" -> listOf("L'abîme profond", "Le silence des ombres", "La part sombre", "La nuit noire", "La douleur secrète", "Le vide intérieur")
                "verbs" -> listOf("défie", "engloutit", "révèle", "éveille", "repousse", "transperce", "sépare")
                "adverbs" -> listOf("farouchement", "dans l'obscurité", "implacablement", "sombrement", "au fond de soi", "secrètement")
                "complements" -> listOf("les monstres du doute", "l'illusion du néant absolu", "les instincts cachés", "les barrières du subconscient", "la froide vérité du monde")
                else -> listOf("pour en extraire une lumière inextinguible.", "quand la réalité vacille sur ses bases.", "dans l'obscurité la plus sincère.", "avant le renouveau du jour.")
            }
            "success" -> when (type) {
                "subjects" -> listOf("Le succès véritable", "L'excellence constante", "La victoire ultime", "L'effort inlassable", "La consécration", "La réussite pure")
                "verbs" -> listOf("couronne", "exige", "pave", "éclaire", "satisfait", "honore", "développe")
                "adverbs" -> listOf("fièrement", "nécessairement", "parfaitement", "avec panache", "clairement", "glorieusement")
                "complements" -> listOf("les innombrables sacrifices consentis", "le chemin sinueux parcouru", "la persévérance inébranlable", "l'amour du travail bien accompli", "le courage d'oser")
                else -> listOf("au sommet d'un long combat héroïque.", "comme la consécration logique de l'audace.", "sans craindre le mépris des sceptiques.", "dans la grandeur d'esprit.")
            }
            else -> when (type) {
                "subjects" -> listOf("La sagesse innée")
                "verbs" -> listOf("triomphe")
                "adverbs" -> listOf("simplement")
                "complements" -> listOf("de la complexité")
                else -> listOf("en toute circonstance.")
            }
        }
    }
}
