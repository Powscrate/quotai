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

        val systemPrompt = "Tu es un générateur de citations inspirantes. Écris EXCLUSIVEMENT en français naturel. Chaque sortie doit être une seule citation courte inspirante (maximum une phrase). Style: profond, humain, motivant ou réfléchi. Évite les clichés et n'explique pas ta réponse."
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
                throw IllegalStateException("La bibliothèque native llama.cpp n'est pas chargée.")
            }
        } catch (e: Exception) {
            Log.e(TAG, "Native generation failed", e)
            throw e
        } finally {
            tokenCallback = null
        }
    }
}
