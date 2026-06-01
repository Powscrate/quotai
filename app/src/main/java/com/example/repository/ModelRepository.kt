package com.example.repository

import android.content.Context
import android.net.Uri
import android.provider.OpenableColumns
import com.example.llama.GgufMetadataReader
import com.example.llama.LlamaCpp
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.withContext
import java.io.File
import java.io.FileOutputStream
import java.io.InputStream
import java.util.Locale

data class ModelInfo(
    val name: String,
    val fileName: String,
    val sizeBytes: Long,
    val path: String,
    val isLoaded: Boolean,
    val quantization: String,
    val architecture: String
)

class ModelRepository(val context: Context) {

    private val PREFS_NAME = "quotai_prefs"
    private val KEY_ACTIVE_MODEL = "active_model_path"
    private val KEY_LOW_MEM_MODE = "low_mem_mode"
    private val sharedPrefs = context.getSharedPreferences(PREFS_NAME, Context.MODE_PRIVATE)

    fun getModelsDir(): File {
        val dir = context.getExternalFilesDir("models") ?: File(context.filesDir, "models")
        if (!dir.exists()) {
            dir.mkdirs()
        }
        return dir
    }

    suspend fun getModelsList(): List<ModelInfo> = withContext(Dispatchers.IO) {
        val dir = getModelsDir()
        val files = dir.listFiles { _, name -> name.endsWith(".gguf") } ?: emptyArray()
        val activePath = getActiveModelPath()

        return@withContext files.map { file ->
            // Try loading metadata or fallback gracefully
            val (name, quant, arch) = try {
                val meta = GgufMetadataReader.readMetadata(file)
                Triple(meta.name, meta.quantization, meta.architecture)
            } catch (e: Exception) {
                val fallbackName = file.nameWithoutExtension.replaceFirstChar { if (it.isLowerCase()) it.titlecase(Locale.getDefault()) else it.toString() }
                Triple(fallbackName, "Inconnue", "llama")
            }

            ModelInfo(
                name = name,
                fileName = file.name,
                sizeBytes = file.length(),
                path = file.absolutePath,
                isLoaded = activePath == file.absolutePath && LlamaCpp.isLoaded(),
                quantization = quant,
                architecture = arch
            )
        }.sortedBy { it.name }
    }

    suspend fun importModel(uri: Uri): File = withContext(Dispatchers.IO) {
        val contentResolver = context.contentResolver
        val fileName = getFileNameFromUri(uri) ?: "imported_model_${System.currentTimeMillis()}.gguf"
        
        if (!fileName.endsWith(".gguf")) {
            throw IllegalArgumentException("Le fichier sélectionné n'est pas un modèle .gguf valide.")
        }

        val targetDir = getModelsDir()
        val targetFile = File(targetDir, fileName)

        contentResolver.openInputStream(uri)?.use { inputStream ->
            FileOutputStream(targetFile).use { outputStream ->
                val buffer = ByteArray(1024 * 1024) // 1MB chunk copying for smooth memory on low-RAM devices
                var bytesRead: Int
                while (inputStream.read(buffer).also { bytesRead = it } != -1) {
                    outputStream.write(buffer, 0, bytesRead)
                }
            }
        } ?: throw IllegalStateException("Impossible d'ouvrir le fichier sélectionné.")

        // Validate the imported GGUF integrity right away
        try {
            GgufMetadataReader.readMetadata(targetFile)
        } catch (e: Exception) {
            targetFile.delete() // Cleanup corrupt/invalid files automatically!
            throw IllegalArgumentException("Fichier GGUF corrompu ou invalide: ${e.message}")
        }

        return@withContext targetFile
    }

    fun deleteModel(file: File): Boolean {
        if (getActiveModelPath() == file.absolutePath) {
            setActiveModelPath(null)
        }
        return file.delete()
    }

    suspend fun downloadModel(
        urlString: String,
        targetFileName: String,
        onProgress: (Float) -> Unit
    ): File = withContext(Dispatchers.IO) {
        val targetDir = getModelsDir()
        val targetFile = File(targetDir, targetFileName)
        
        if (targetFile.exists()) {
            targetFile.delete()
        }

        val url = java.net.URL(urlString)
        val connection = url.openConnection() as java.net.HttpURLConnection
        connection.connectTimeout = 30000
        connection.readTimeout = 30000
        connection.connect()

        if (connection.responseCode != java.net.HttpURLConnection.HTTP_OK) {
            throw java.io.IOException("Le serveur a retourné le code : ${connection.responseCode} ${connection.responseMessage}")
        }

        val fileLength = connection.contentLengthLong
        connection.inputStream.use { inputStream ->
            java.io.FileOutputStream(targetFile).use { outputStream ->
                val buffer = ByteArray(1024 * 1024) // 1MB buffer
                var bytesRead: Int
                var totalBytesRead = 0L
                while (inputStream.read(buffer).also { bytesRead = it } != -1) {
                    outputStream.write(buffer, 0, bytesRead)
                    totalBytesRead += bytesRead
                    if (fileLength > 0) {
                        onProgress(totalBytesRead.toFloat() / fileLength.toFloat())
                    } else {
                        onProgress(-1f)
                    }
                }
            }
        }

        // Validate GGUF integrity right away
        try {
            GgufMetadataReader.readMetadata(targetFile)
        } catch (e: Exception) {
            targetFile.delete() // Cleanup automatically!
            throw IllegalArgumentException("Fichier GGUF téléchargé corrompu ou invalide : ${e.message}")
        }

        return@withContext targetFile
    }

    fun getActiveModelPath(): String? {
        return sharedPrefs.getString(KEY_ACTIVE_MODEL, null)
    }

    fun setActiveModelPath(path: String?) {
        sharedPrefs.edit().putString(KEY_ACTIVE_MODEL, path).apply()
    }

    fun isLowMemoryMode(): Boolean {
        return sharedPrefs.getBoolean(KEY_LOW_MEM_MODE, true) // Enable low-mem mode by default for safety!
    }

    fun setLowMemoryMode(enabled: Boolean) {
        sharedPrefs.edit().putBoolean(KEY_LOW_MEM_MODE, enabled).apply()
    }

    private fun getFileNameFromUri(uri: Uri): String? {
        var name: String? = null
        val cursor = context.contentResolver.query(uri, null, null, null, null)
        cursor?.use {
            if (it.moveToFirst()) {
                val nameIndex = it.getColumnIndex(OpenableColumns.DISPLAY_NAME)
                if (nameIndex != -1) {
                    name = it.getString(nameIndex)
                }
            }
        }
        return name
    }
}
