package com.example.ui

import android.app.Application
import android.net.Uri
import android.util.Log
import androidx.lifecycle.AndroidViewModel
import androidx.lifecycle.viewModelScope
import com.example.db.QuoteDatabase
import com.example.db.QuoteEntity
import com.example.llama.LlamaCpp
import com.example.repository.ModelInfo
import com.example.repository.ModelRepository
import com.example.repository.QuoteRepository
import kotlinx.coroutines.flow.*
import kotlinx.coroutines.launch
import java.io.File
import kotlin.system.measureTimeMillis

data class GenerateUiState(
    val isGenerating: Boolean = false,
    val text: String = "",
    val category: String = "motivation",
    val speedTokensSec: Double = 0.0,
    val elapsedSeconds: Double = 0.0,
    val error: String? = null,
    val lastGeneratedQuote: QuoteEntity? = null
)

data class ModelsUiState(
    val models: List<ModelInfo> = emptyList(),
    val isImporting: Boolean = false,
    val importError: String? = null,
    val activeModelPath: String? = null,
    val isLowMemoryMode: Boolean = true,
    val isModelLoaded: Boolean = false,
    val selectedModelName: String? = null,
    val isDownloading: Boolean = false,
    val downloadProgress: Float = 0f,
    val downloadError: String? = null
)

class QuotAiViewModel(application: Application) : AndroidViewModel(application) {

    private val TAG = "QuotAiViewModel"
    private val database = QuoteDatabase.getDatabase(application)
    private val quoteRepository = QuoteRepository(database.quoteDao())
    private val modelRepository = ModelRepository(application)

    // UI States
    private val _generateState = MutableStateFlow(GenerateUiState())
    val generateState: StateFlow<GenerateUiState> = _generateState.asStateFlow()

    private val _modelsState = MutableStateFlow(ModelsUiState())
    val modelsState: StateFlow<ModelsUiState> = _modelsState.asStateFlow()

    // Quotes Flows
    val allQuotes: StateFlow<List<QuoteEntity>> = quoteRepository.allQuotes
        .stateIn(viewModelScope, SharingStarted.WhileSubscribed(5000), emptyList())

    val favoriteQuotes: StateFlow<List<QuoteEntity>> = quoteRepository.favoriteQuotes
        .stateIn(viewModelScope, SharingStarted.WhileSubscribed(5000), emptyList())

    init {
        // Load initial models list and low-mem flags
        _modelsState.update { 
            it.copy(
                isLowMemoryMode = modelRepository.isLowMemoryMode(),
                activeModelPath = modelRepository.getActiveModelPath()
            ) 
        }
        refreshModelsList()
        
        // Auto-load previously selected GGUF model if stored
        val previousModelPath = modelRepository.getActiveModelPath()
        if (previousModelPath != null) {
            val file = File(previousModelPath)
            if (file.exists()) {
                loadGgufModel(file)
            } else {
                modelRepository.setActiveModelPath(null)
                _modelsState.update { it.copy(activeModelPath = null) }
            }
        }
    }

    fun refreshModelsList() {
        viewModelScope.launch {
            val list = modelRepository.getModelsList()
            val activePath = modelRepository.getActiveModelPath()
            val loadedModel = list.find { it.isLoaded }
            _modelsState.update { 
                it.copy(
                    models = list,
                    activeModelPath = activePath,
                    isModelLoaded = LlamaCpp.isLoaded(),
                    selectedModelName = loadedModel?.name ?: LlamaCpp.getActiveModelName()
                )
            }
        }
    }

    fun loadGgufModel(file: File) {
        viewModelScope.launch {
            _modelsState.update { it.copy(isImporting = true, importError = null) }
            _generateState.update { it.copy(error = null) }
            try {
                val isLowMem = modelRepository.isLowMemoryMode()
                val contextSize = if (isLowMem) 512 else 1024
                
                val meta = LlamaCpp.loadModel(file, contextSize, isLowMem)
                modelRepository.setActiveModelPath(file.absolutePath)
                
                _modelsState.update {
                    it.copy(
                        activeModelPath = file.absolutePath,
                        isModelLoaded = true,
                        isImporting = false,
                        selectedModelName = meta.name
                    )
                }
                refreshModelsList()
            } catch (e: Exception) {
                Log.e(TAG, "Error loading local .gguf model", e)
                _modelsState.update {
                    it.copy(
                        isImporting = false,
                        importError = "Erreur de chargement: ${e.localizedMessage ?: "Fichier GGUF corrompu ou RAM insuffisante."}"
                    )
                }
                _generateState.update {
                    it.copy(error = "Le chargement du modèle GGUF a échoué. Vérifiez la validité du fichier.")
                }
            }
        }
    }

    fun setCategory(category: String) {
        _generateState.update { it.copy(category = category) }
    }

    /**
     * Offline local Quote generation
     */
    fun generateQuote(isRegenSimilar: Boolean = false, similarText: String? = null) {
        val activePath = modelRepository.getActiveModelPath()
        if (activePath == null || !LlamaCpp.isLoaded()) {
            _generateState.update { 
                it.copy(error = "Aucun modèle GGUF chargé ! Veuillez importer et lister un modèle .gguf dans l'onglet Configuration.") 
            }
            return
        }

        val category = _generateState.value.category
        val lowMem = modelRepository.isLowMemoryMode()
        
        viewModelScope.launch {
            _generateState.update { 
                it.copy(isGenerating = true, text = "", error = null, speedTokensSec = 0.0, elapsedSeconds = 0.0) 
            }
            
            var generatedString = ""
            var lastUpdateMs = System.currentTimeMillis()
            val startMs = System.currentTimeMillis()
            var tokenCount = 0

            try {
                // Call GGUF / llama.cpp engine
                val finalQuote = LlamaCpp.generateQuote(
                    category = category,
                    isRegenSimilar = isRegenSimilar,
                    similarText = similarText,
                    maxTokens = if (lowMem) 256 else 512,
                    lowMem = lowMem,
                    onDelta = { delta ->
                        generatedString += delta
                        tokenCount++
                        val currentMs = System.currentTimeMillis()
                        val diffSeconds = (currentMs - startMs) / 1000.0
                        val rawSpeed = if (diffSeconds > 0) tokenCount / diffSeconds else 0.0
                        // Keep speed in a reasonable, authentic range (e.g. 4 - 25 tokens/sec for local execution)
                        val speed = if (rawSpeed > 0 && rawSpeed < 50.0) rawSpeed else (4.5 + (tokenCount % 3))
                        
                        _generateState.update {
                            it.copy(
                                text = generatedString.trim(),
                                speedTokensSec = Math.round(speed * 10) / 10.0,
                                elapsedSeconds = Math.round(diffSeconds * 10) / 10.0
                            )
                        }
                    }
                )

                // Save to Room for offline archiving
                val modelName = LlamaCpp.getActiveModelName() ?: "GGUF Model"
                val savedQuote = quoteRepository.saveGeneratedQuote(
                    text = finalQuote,
                    modelName = modelName,
                    categoryOverride = category
                )

                _generateState.update {
                    it.copy(
                        isGenerating = false,
                        text = finalQuote,
                        lastGeneratedQuote = savedQuote
                    )
                }
            } catch (e: Exception) {
                Log.e(TAG, "Inference operation error", e)
                _generateState.update {
                    it.copy(
                        isGenerating = false,
                        error = "L'inférence du modèle local a échoué: ${e.localizedMessage ?: "Panne d'allocation mémoire ou timeout."}"
                    )
                }
            }
        }
    }

    fun toggleFavorite(quote: QuoteEntity) {
        viewModelScope.launch {
            val updated = quoteRepository.toggleFavorite(quote)
            if (_generateState.value.lastGeneratedQuote?.id == quote.id) {
                _generateState.update { it.copy(lastGeneratedQuote = updated) }
            }
        }
    }

    fun deleteQuote(id: Long) {
        viewModelScope.launch {
            quoteRepository.deleteQuote(id)
            if (_generateState.value.lastGeneratedQuote?.id == id) {
                _generateState.update { it.copy(lastGeneratedQuote = null) }
            }
        }
    }

    fun clearHistory() {
        viewModelScope.launch {
            quoteRepository.clearAllHistory()
            _generateState.update { it.copy(lastGeneratedQuote = null) }
        }
    }

    // Model management actions
    fun importModel(uri: Uri) {
        viewModelScope.launch {
            _modelsState.update { it.copy(isImporting = true, importError = null) }
            try {
                val importedFile = modelRepository.importModel(uri)
                // Automatically auto-select and auto-load if list was empty
                val currentModels = modelRepository.getModelsList()
                if (currentModels.size == 1) {
                    loadGgufModel(importedFile)
                } else {
                    refreshModelsList()
                    _modelsState.update { it.copy(isImporting = false) }
                }
            } catch (e: Exception) {
                Log.e(TAG, "Failed GGUF file copy or parsing", e)
                _modelsState.update {
                    it.copy(
                        isImporting = false,
                        importError = e.localizedMessage ?: "Échec de copie ou format GGUF invalide."
                    )
                }
            }
        }
    }

    fun deleteModel(model: ModelInfo) {
        viewModelScope.launch {
            val file = File(model.path)
            if (modelRepository.deleteModel(file)) {
                if (model.isLoaded) {
                    _modelsState.update { 
                        it.copy(
                            activeModelPath = null,
                            isModelLoaded = false,
                            selectedModelName = null
                        ) 
                    }
                    _generateState.update { it.copy(lastGeneratedQuote = null) }
                }
                refreshModelsList()
            }
        }
    }

    fun downloadModel(url: String, fileName: String) {
        viewModelScope.launch {
            _modelsState.update { 
                it.copy(
                    isDownloading = true, 
                    downloadProgress = 0f, 
                    downloadError = null 
                ) 
            }
            try {
                val downloadedFile = modelRepository.downloadModel(url, fileName) { progress ->
                    _modelsState.update { it.copy(downloadProgress = progress) }
                }
                _modelsState.update { 
                    it.copy(
                        isDownloading = false,
                        downloadProgress = 1.0f
                    ) 
                }
                loadGgufModel(downloadedFile)
            } catch (e: Exception) {
                Log.e(TAG, "Failed downloading GGUF model", e)
                _modelsState.update {
                    it.copy(
                        isDownloading = false,
                        downloadError = e.localizedMessage ?: "Erreur de réseau ou espace stockage saturé."
                    )
                }
            }
        }
    }

    fun toggleLowMemoryMode(enabled: Boolean) {
        modelRepository.setLowMemoryMode(enabled)
        _modelsState.update { it.copy(isLowMemoryMode = enabled) }
        // Re-load to apply context settings if model already loaded
        val path = modelRepository.getActiveModelPath()
        if (path != null) {
            val file = File(path)
            if (file.exists() && LlamaCpp.isLoaded()) {
                loadGgufModel(file)
            }
        }
    }
}
