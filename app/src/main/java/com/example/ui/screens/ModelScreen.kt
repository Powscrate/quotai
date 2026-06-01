package com.example.ui.screens

import android.net.Uri
import androidx.activity.compose.rememberLauncherForActivityResult
import androidx.activity.result.contract.ActivityResultContracts
import androidx.compose.animation.*
import androidx.compose.foundation.BorderStroke
import androidx.compose.foundation.background
import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.*
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.lazy.items
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.*
import androidx.compose.material.icons.outlined.Delete
import androidx.compose.material.icons.outlined.FileOpen
import androidx.compose.material3.*
import androidx.compose.runtime.*
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.platform.LocalContext
import androidx.compose.ui.platform.testTag
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.text.style.TextAlign
import androidx.compose.ui.text.style.TextOverflow
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import com.example.repository.ModelInfo
import com.example.ui.ModelsUiState
import com.example.ui.QuotAiViewModel
import com.example.ui.theme.*
import java.io.File

@Composable
fun ModelScreen(
    viewModel: QuotAiViewModel,
    modifier: Modifier = Modifier
) {
    val modelsState by viewModel.modelsState.collectAsState()
    var hfUrlInput by remember { mutableStateOf("") }

    val filePickerLauncher = rememberLauncherForActivityResult(
        contract = ActivityResultContracts.GetContent()
    ) { uri: Uri? ->
        uri?.let { viewModel.importModel(it) }
    }

    LazyColumn(
        modifier = modifier
            .fillMaxSize()
            .padding(16.dp),
        verticalArrangement = Arrangement.spacedBy(16.dp)
    ) {
        // High capabilities: RAM limit optimizations
        item {
            LowRamOptimizerCard(
                isLowMem = modelsState.isLowMemoryMode,
                onToggle = { viewModel.toggleLowMemoryMode(it) }
            )
        }

        // Section Title: import actions
        item {
            Text(
                text = "IMPORTER UN NOUVEAU MODÈLE",
                fontSize = 11.sp,
                fontWeight = FontWeight.Bold,
                color = MutedText,
                modifier = Modifier.padding(start = 4.dp)
            )
        }

        item {
            Card(
                shape = RoundedCornerShape(16.dp),
                colors = CardDefaults.cardColors(containerColor = SpaceCard),
                border = BorderStroke(1.dp, SurfaceBorder),
                modifier = Modifier.fillMaxWidth()
            ) {
                Column(
                    modifier = Modifier.padding(16.dp),
                    horizontalAlignment = Alignment.CenterHorizontally
                ) {
                    Icon(
                        imageVector = Icons.Outlined.FileOpen,
                        contentDescription = null,
                        tint = CyanTech,
                        modifier = Modifier.size(40.dp)
                    )

                    Spacer(modifier = Modifier.height(8.dp))

                    Text(
                        text = "Importer depuis le stockage local des fichiers",
                        fontSize = 13.sp,
                        fontWeight = FontWeight.Medium,
                        color = LightGreyText,
                        textAlign = TextAlign.Center
                    )

                    Text(
                        text = "Sélectionnez un modèle valide au format .gguf (ex: Q4_K_M).",
                        fontSize = 11.sp,
                        color = MutedText,
                        textAlign = TextAlign.Center,
                        modifier = Modifier.padding(top = 2.dp, bottom = 12.dp)
                    )

                    Button(
                        onClick = { filePickerLauncher.launch("*/*") },
                        enabled = !modelsState.isImporting,
                        colors = ButtonDefaults.buttonColors(containerColor = CyanTech),
                        modifier = Modifier
                            .fillMaxWidth()
                            .testTag("import_model_file_btn")
                    ) {
                        Text(
                            text = if (modelsState.isImporting) "IMPORTATION EN COURS..." else "SÉLECTIONNER UN CONTEXTE .GGUF",
                            color = SpaceBlack,
                            fontWeight = FontWeight.Bold
                        )
                    }

                    if (modelsState.isImporting) {
                        Spacer(modifier = Modifier.height(12.dp))
                        CircularProgressIndicator(color = CyanTech, modifier = Modifier.size(24.dp))
                        Spacer(modifier = Modifier.height(4.dp))
                        Text(
                            text = "Copie et extraction des tenseurs binaires dans le stockage de l'app. Ne quittez pas l'écran.",
                            fontSize = 10.sp,
                            color = MutedText,
                            textAlign = TextAlign.Center
                        )
                    }

                    modelsState.importError?.let { err ->
                        Spacer(modifier = Modifier.height(8.dp))
                        Text(
                            text = err,
                            color = SoftRed,
                            fontSize = 12.sp,
                            textAlign = TextAlign.Center,
                            fontWeight = FontWeight.SemiBold
                        )
                    }
                }
            }
        }

        // Section: Real GGUF model download options
        item {
            Text(
                text = "TÉLÉCHARGER DES MODÈLES SÉLECTIONNÉS (OFFLINE)",
                fontSize = 11.sp,
                fontWeight = FontWeight.Bold,
                color = MutedText,
                modifier = Modifier.padding(start = 4.dp)
            )
        }

        item {
            val presetModels = listOf(
                Triple(
                    "SmolLM 135M (Recommandé Low-RAM)",
                    "https://huggingface.co/second-state/SmolLM-135M-Instruct-GGUF/resolve/main/SmolLM-135M-Instruct-Q4_K_M.gguf",
                    "SmolLM_135M_Instruct_Q4_K_M.gguf"
                ),
                Triple(
                    "Qwen 0.5B Chat (Rapide & Intelligent)",
                    "https://huggingface.co/Qwen/Qwen1.5-0.5B-Chat-GGUF/resolve/main/qwen1.5-0.5b-chat-q2_k.gguf",
                    "Qwen_0.5B_Chat_Q2_K.gguf"
                ),
                Triple(
                    "DanLa 1.1B (Français Avancé)",
                    "https://huggingface.co/TheBloke/DanLa-1.1B-GGUF/resolve/main/DanLa-1.1B-Q4_K_M.gguf",
                    "DanLa_1.1B_Q4_K_M.gguf"
                )
            )

            Card(
                shape = RoundedCornerShape(16.dp),
                colors = CardDefaults.cardColors(containerColor = SpaceCard),
                border = BorderStroke(1.dp, SurfaceBorder),
                modifier = Modifier.fillMaxWidth()
            ) {
                Column(modifier = Modifier.padding(16.dp)) {
                    Text(
                        text = "Téléchargement direct de modèles d'IA",
                        fontSize = 14.sp,
                        fontWeight = FontWeight.Bold,
                        color = Color.White
                    )
                    Spacer(modifier = Modifier.height(6.dp))
                    Text(
                        text = "Choisissez l'un de nos modèles présélectionnés ultra-légers pour débuter instantanément avec llama.cpp hors-ligne, ou collez une adresse URL personnalisée ci-dessous.",
                        fontSize = 11.sp,
                        color = MutedText,
                        lineHeight = 15.sp
                    )

                    Spacer(modifier = Modifier.height(14.dp))

                    presetModels.forEach { (name, url, file) ->
                        OutlinedButton(
                            onClick = { viewModel.downloadModel(url, file) },
                            enabled = !modelsState.isDownloading && !modelsState.isImporting,
                            border = BorderStroke(1.dp, VelvetIndigo.copy(alpha = 0.5f)),
                            colors = ButtonDefaults.outlinedButtonColors(contentColor = Color.White),
                            shape = RoundedCornerShape(8.dp),
                            modifier = Modifier
                                .fillMaxWidth()
                                .padding(vertical = 4.dp)
                        ) {
                            Row(
                                modifier = Modifier.fillMaxWidth(),
                                horizontalArrangement = Arrangement.SpaceBetween,
                                verticalAlignment = Alignment.CenterVertically
                            ) {
                                Row(verticalAlignment = Alignment.CenterVertically) {
                                    Icon(
                                        imageVector = Icons.Default.CloudDownload,
                                        contentDescription = null,
                                        tint = CyanTech,
                                        modifier = Modifier.size(16.dp)
                                    )
                                    Spacer(modifier = Modifier.width(8.dp))
                                    Text(name, fontSize = 12.sp, fontWeight = FontWeight.Bold)
                                }
                                Text(
                                    text = if (file.contains("135M")) "90 Mo" else if (file.contains("0.5B")) "350 Mo" else "730 Mo",
                                    fontSize = 10.sp,
                                    color = CyanTech,
                                    fontWeight = FontWeight.Bold
                                )
                            }
                        }
                    }

                    Spacer(modifier = Modifier.height(12.dp))
                    HorizontalDivider(color = SurfaceBorder, thickness = 1.dp)
                    Spacer(modifier = Modifier.height(12.dp))

                    Text(
                        text = "Adresse URL GGUF Personnalisée",
                        fontSize = 12.sp,
                        fontWeight = FontWeight.Bold,
                        color = Color.White
                    )
                    Spacer(modifier = Modifier.height(4.dp))

                    TextField(
                        value = hfUrlInput,
                        onValueChange = { hfUrlInput = it },
                        placeholder = { Text("https://huggingface.co/...", color = MutedText, fontSize = 11.sp) },
                        colors = TextFieldDefaults.colors(
                            focusedTextColor = Color.White,
                            unfocusedTextColor = Color.White,
                            focusedContainerColor = DarkGrey,
                            unfocusedContainerColor = DarkGrey,
                            focusedIndicatorColor = Color.Transparent,
                            unfocusedIndicatorColor = Color.Transparent
                        ),
                        shape = RoundedCornerShape(8.dp),
                        singleLine = true,
                        modifier = Modifier
                            .fillMaxWidth()
                            .height(48.dp)
                    )

                    Spacer(modifier = Modifier.height(8.dp))

                    Button(
                        onClick = {
                            val detectedFileName = hfUrlInput.substringAfterLast("/").substringBefore("?").ifBlank { "custom_model.gguf" }
                            val cleanFileName = if (detectedFileName.endsWith(".gguf")) detectedFileName else "$detectedFileName.gguf"
                            viewModel.downloadModel(hfUrlInput, cleanFileName)
                        },
                        enabled = hfUrlInput.isNotBlank() && !modelsState.isDownloading && !modelsState.isImporting,
                        colors = ButtonDefaults.buttonColors(containerColor = VelvetIndigo),
                        shape = RoundedCornerShape(8.dp),
                        modifier = Modifier.fillMaxWidth()
                    ) {
                        Text("TÉLÉCHARGER URL PERSONNALISÉE", fontWeight = FontWeight.Bold, fontSize = 12.sp)
                    }

                    // Progress reporting
                    if (modelsState.isDownloading) {
                        val progress = modelsState.downloadProgress
                        val pct = if (progress >= 0f) "${(progress * 100).toInt()}%" else "Téléchargement..."
                        Spacer(modifier = Modifier.height(14.dp))
                        
                        if (progress >= 0f) {
                            LinearProgressIndicator(
                                progress = { progress },
                                color = CyanTech,
                                trackColor = DarkGrey,
                                modifier = Modifier.fillMaxWidth()
                            )
                        } else {
                            LinearProgressIndicator(
                                color = CyanTech,
                                trackColor = DarkGrey,
                                modifier = Modifier.fillMaxWidth()
                            )
                        }
                        
                        Spacer(modifier = Modifier.height(4.dp))
                        Row(
                            horizontalArrangement = Arrangement.SpaceBetween,
                            modifier = Modifier.fillMaxWidth()
                        ) {
                            Text("Téléchargement du fichier de tenseurs GGUF...", fontSize = 11.sp, color = MutedText)
                            Text(pct, fontSize = 11.sp, color = CyanTech, fontWeight = FontWeight.Bold)
                        }
                    }

                    modelsState.downloadError?.let { err ->
                        Spacer(modifier = Modifier.height(8.dp))
                        Text(
                            text = "Erreur: $err",
                            color = SoftRed,
                            fontSize = 11.sp,
                            fontWeight = FontWeight.SemiBold,
                            textAlign = TextAlign.Center,
                            modifier = Modifier.fillMaxWidth()
                        )
                    }
                }
            }
        }

        // Section Title: Model library list
        item {
            Text(
                text = "VOTRE BIBLIOTHÈQUE DE MODÈLES (.GGUF)",
                fontSize = 11.sp,
                fontWeight = FontWeight.Bold,
                color = MutedText,
                modifier = Modifier.padding(start = 4.dp)
            )
        }

        if (modelsState.models.isEmpty()) {
            item {
                Card(
                    shape = RoundedCornerShape(16.dp),
                    colors = CardDefaults.cardColors(containerColor = SpaceCard),
                    border = BorderStroke(1.dp, SurfaceBorder.copy(alpha = 0.5f)),
                    modifier = Modifier.fillMaxWidth()
                ) {
                    Column(
                        modifier = Modifier
                            .padding(24.dp)
                            .fillMaxWidth(),
                        horizontalAlignment = Alignment.CenterHorizontally
                    ) {
                        Icon(
                            imageVector = Icons.Default.Inbox,
                            contentDescription = null,
                            tint = MutedText.copy(alpha = 0.4f),
                            modifier = Modifier.size(42.dp)
                        )
                        Spacer(modifier = Modifier.height(8.dp))
                        Text(
                            text = "Bibliothèque de modèles vide",
                            fontWeight = FontWeight.SemiBold,
                            color = LightGreyText,
                            fontSize = 13.sp
                        )
                        Text(
                            text = "Importez un fichier .gguf de petite taille (ex: DanLa_1.1B-Q4_K_M) pour débuter l'expérience.",
                            color = MutedText,
                            fontSize = 11.sp,
                            textAlign = TextAlign.Center,
                            modifier = Modifier.padding(top = 4.dp)
                        )
                    }
                }
            }
        } else {
            items(modelsState.models, key = { it.path }) { model ->
                ModelItemRow(
                    model = model,
                    onSelect = { viewModel.loadGgufModel(File(model.path)) },
                    onDelete = { viewModel.deleteModel(model) }
                )
            }
        }
    }
}

@Composable
fun LowRamOptimizerCard(
    isLowMem: Boolean,
    onToggle: (Boolean) -> Unit
) {
    Card(
        shape = RoundedCornerShape(16.dp),
        colors = CardDefaults.cardColors(containerColor = SpaceCard),
        border = BorderStroke(1.dp, SurfaceBorder),
        modifier = Modifier.fillMaxWidth()
    ) {
        Row(
            modifier = Modifier
                .fillMaxWidth()
                .padding(16.dp),
            verticalAlignment = Alignment.CenterVertically
        ) {
            Icon(
                imageVector = Icons.Default.Memory,
                contentDescription = null,
                tint = VelvetIndigo,
                modifier = Modifier.size(32.dp)
            )

            Spacer(modifier = Modifier.width(16.dp))

            Column(modifier = Modifier.weight(1.0f)) {
                Text(
                    text = "Mode Basse Mémoire (RAM)",
                    fontWeight = FontWeight.Bold,
                    fontSize = 14.sp,
                    color = Color.White
                )
                Text(
                    text = "Active des allocations CPU serrées et limite le contexte à 512 tokens. Recommandé pour téléphones modestes de 1 à 2 Go de RAM.",
                    fontSize = 11.sp,
                    color = MutedText,
                    lineHeight = 15.sp,
                    modifier = Modifier.padding(top = 2.dp)
                )
            }

            Spacer(modifier = Modifier.width(8.dp))

            Switch(
                checked = isLowMem,
                onCheckedChange = onToggle,
                colors = SwitchDefaults.colors(
                    checkedThumbColor = SpaceBlack,
                    checkedTrackColor = CyanTech,
                    uncheckedThumbColor = MutedText,
                    uncheckedTrackColor = DarkGrey,
                    uncheckedBorderColor = Color.Transparent
                ),
                modifier = Modifier.testTag("low_ram_switch")
            )
        }
    }
}

@Composable
fun ModelItemRow(
    model: ModelInfo,
    onSelect: () -> Unit,
    onDelete: () -> Unit
) {
    // Math size conversions
    val sizeInMb = remember(model.sizeBytes) {
        Math.round((model.sizeBytes / (1024.0 * 1024.0)) * 10) / 10.0
    }

    Card(
        shape = RoundedCornerShape(16.dp),
        colors = CardDefaults.cardColors(
            containerColor = if (model.isLoaded) SpaceCard else SpaceCard.copy(alpha = 0.5f)
        ),
        border = BorderStroke(
            width = if (model.isLoaded) 2.dp else 1.dp,
            color = if (model.isLoaded) CyanTech else SurfaceBorder
        ),
        modifier = Modifier
            .fillMaxWidth()
            .clickable { onSelect() }
            .testTag("model_item_${model.fileName}")
    ) {
        Row(
            modifier = Modifier
                .fillMaxWidth()
                .padding(16.dp),
            verticalAlignment = Alignment.CenterVertically,
            horizontalArrangement = Arrangement.SpaceBetween
        ) {
            Row(
                verticalAlignment = Alignment.CenterVertically,
                modifier = Modifier.weight(1f)
            ) {
                Icon(
                    imageVector = Icons.Default.DeveloperBoard,
                    contentDescription = null,
                    tint = if (model.isLoaded) CyanTech else MutedText,
                    modifier = Modifier.size(28.dp)
                )

                Spacer(modifier = Modifier.width(16.dp))

                Column {
                    Row(verticalAlignment = Alignment.CenterVertically) {
                        Text(
                            text = model.name,
                            fontWeight = FontWeight.Bold,
                            fontSize = 14.sp,
                            color = Color.White,
                            maxLines = 1,
                            overflow = TextOverflow.Ellipsis,
                            modifier = Modifier.widthIn(max = 160.dp)
                        )
                        if (model.isLoaded) {
                            Spacer(modifier = Modifier.width(6.dp))
                            Surface(
                                color = CyanTech.copy(alpha = 0.15f),
                                shape = RoundedCornerShape(4.dp)
                            ) {
                                Text(
                                    text = "CHARGÉ",
                                    color = CyanTech,
                                    fontSize = 8.sp,
                                    fontWeight = FontWeight.Bold,
                                    modifier = Modifier.padding(horizontal = 4.dp, vertical = 2.dp)
                                )
                            }
                        }
                    }

                    Row(
                        verticalAlignment = Alignment.CenterVertically,
                        modifier = Modifier.padding(top = 2.dp)
                    ) {
                        Text(text = "$sizeInMb Mo", fontSize = 11.sp, color = MutedText)
                        Spacer(modifier = Modifier.width(8.dp))
                        Box(modifier = Modifier.size(3.dp).background(color = MutedText, shape = RoundedCornerShape(1.5.dp)))
                        Spacer(modifier = Modifier.width(8.dp))
                        Text(text = model.quantization, fontSize = 11.sp, color = MutedText)
                        Spacer(modifier = Modifier.width(8.dp))
                        Box(modifier = Modifier.size(3.dp).background(color = MutedText, shape = RoundedCornerShape(1.5.dp)))
                        Spacer(modifier = Modifier.width(8.dp))
                        Text(text = model.architecture, fontSize = 11.sp, color = VelvetIndigo, fontWeight = FontWeight.SemiBold)
                    }
                }
            }

            IconButton(
                onClick = onDelete,
                modifier = Modifier.testTag("delete_model_btn_${model.fileName}")
            ) {
                Icon(imageVector = Icons.Outlined.Delete, contentDescription = "Supprimer", tint = SoftRed)
            }
        }
    }
}
