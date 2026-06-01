package com.example.llama

import java.io.File
import java.io.FileInputStream
import java.nio.ByteBuffer
import java.nio.ByteOrder

data class GgufMetadata(
    val name: String,
    val architecture: String,
    val sizeBytes: Long,
    val version: Int,
    val tensorCount: Long,
    val kvCount: Long,
    val quantization: String
)

object GgufMetadataReader {
    fun readMetadata(file: File): GgufMetadata {
        val sizeBytes = file.length()
        if (!file.exists()) {
            throw IllegalArgumentException("Fichier introuvable.")
        }
        
        FileInputStream(file).use { fis ->
            val headerBytes = ByteArray(1024 * 128) // 128KB of headers
            val bytesRead = fis.read(headerBytes)
            if (bytesRead < 24) {
                throw IllegalArgumentException("Fichier trop petit pour être un modèle GGUF valide.")
            }
            
            val buffer = ByteBuffer.wrap(headerBytes, 0, bytesRead).order(ByteOrder.LITTLE_ENDIAN)
            
            // 1. Magic GGUF signature checking
            val magic = ByteArray(4)
            buffer.get(magic)
            val magicStr = String(magic, Charsets.US_ASCII)
            if (magicStr != "GGUF") {
                throw IllegalArgumentException("Signature magique GGUF invalide. Ce fichier n'est pas un modèle GGUF.")
            }
            
            // 2. Version parse (uint32)
            val version = buffer.getInt()
            if (version != 1 && version != 2 && version != 3) {
                throw IllegalArgumentException("Version GGUF non supportée: $version. QuotAI requiert GGUF v1, v2 ou v3.")
            }
            
            // 3. Tensor count (uint64)
            val tensorCount = buffer.getLong()
            
            // 4. KV pair count (uint64)
            val kvCount = buffer.getLong()
            
            var modelName = "Modèle Inconnu"
            var architecture = "Inconnue"
            var quantization = "Inconnue"
            
            try {
                for (i in 0 until kvCount.toInt()) {
                    if (buffer.remaining() < 8) break
                    val keyLen = buffer.getLong()
                    if (keyLen <= 0 || keyLen > 512 || buffer.remaining() < keyLen) break
                    
                    val keyBytes = ByteArray(keyLen.toInt())
                    buffer.get(keyBytes)
                    val key = String(keyBytes, Charsets.UTF_8)
                    
                    if (buffer.remaining() < 4) break
                    val type = buffer.getInt()
                    
                    when (type) {
                        0 -> buffer.get() // UINT8
                        1 -> buffer.get() // INT8
                        2 -> buffer.getShort() // UINT16
                        3 -> buffer.getShort() // INT16
                        4 -> buffer.getInt() // UINT32
                        5 -> buffer.getInt() // INT32
                        6 -> buffer.getFloat() // FLOAT32
                        7 -> buffer.get() // BOOL
                        8 -> { // STRING
                            if (buffer.remaining() < 8) break
                            val strLen = buffer.getLong()
                            if (strLen in 1..2048 && buffer.remaining() >= strLen) {
                                val strBytes = ByteArray(strLen.toInt())
                                buffer.get(strBytes)
                                val strVal = String(strBytes, Charsets.UTF_8)
                                when (key) {
                                    "general.name" -> modelName = strVal
                                    "general.architecture" -> architecture = strVal
                                    "general.quantization_version", "general.file_type" -> quantization = "Q" + strVal
                                }
                            } else {
                                break
                            }
                        }
                        9 -> { // ARRAY
                            if (buffer.remaining() < 12) break
                            val valType = buffer.getInt()
                            val arrLength = buffer.getLong()
                            val elementSize = when (valType) {
                                0, 1, 7 -> 1
                                2, 3 -> 2
                                4, 5, 6 -> 4
                                10, 11, 12 -> 8
                                8 -> -1
                                else -> 0
                            }
                            if (elementSize > 0) {
                                val totalToSkip = (arrLength * elementSize).toInt()
                                if (buffer.remaining() >= totalToSkip) {
                                    buffer.position(buffer.position() + totalToSkip)
                                } else {
                                    break
                                }
                            } else if (valType == 8) {
                                var aborted = false
                                for (j in 0 until arrLength.toInt()) {
                                    if (buffer.remaining() < 8) { aborted = true; break }
                                    val sLen = buffer.getLong()
                                    if (sLen in 0..1024 && buffer.remaining() >= sLen) {
                                        buffer.position(buffer.position() + sLen.toInt())
                                    } else {
                                        aborted = true
                                        break
                                    }
                                }
                                if (aborted) break
                            }
                        }
                        10 -> buffer.getLong() // UINT64
                        11 -> buffer.getLong() // INT64
                        12 -> buffer.getDouble() // FLOAT64
                    }
                }
            } catch (e: Exception) {
                // Graceful recover from partial buffers
            }
            
            if (quantization == "Inconnue") {
                val lowercaseName = file.name.lowercase()
                quantization = when {
                    lowercaseName.contains("q4_k_m") -> "Q4_K_M"
                    lowercaseName.contains("q4_0") -> "Q4_0"
                    lowercaseName.contains("q4_1") -> "Q4_1"
                    lowercaseName.contains("q8_0") -> "Q8_0"
                    lowercaseName.contains("q2_k") -> "Q2_K"
                    lowercaseName.contains("q3_k_l") -> "Q3_K_L"
                    lowercaseName.contains("q5_k_m") -> "Q5_K_M"
                    lowercaseName.contains("q6_k") -> "Q6_K"
                    lowercaseName.contains("f16") -> "F16"
                    else -> "Q4_K_M (Déduit)"
                }
            }
            
            if (modelName == "Modèle Inconnu") {
                modelName = file.nameWithoutExtension.replace("-", " ").replace("_", " ").capitalize()
            }
            
            if (architecture == "Inconnue") {
                val lowercaseName = file.name.lowercase()
                architecture = when {
                    lowercaseName.contains("llama") -> "llama"
                    lowercaseName.contains("mistral") -> "mistral"
                    lowercaseName.contains("phi") -> "phi"
                    lowercaseName.contains("gemma") -> "gemma"
                    lowercaseName.contains("qwen") -> "qwen"
                    else -> "generic-transformer"
                }
            }
            
            return GgufMetadata(
                name = modelName,
                architecture = architecture,
                sizeBytes = sizeBytes,
                version = version,
                tensorCount = tensorCount,
                kvCount = kvCount,
                quantization = quantization
            )
        }
    }
}
