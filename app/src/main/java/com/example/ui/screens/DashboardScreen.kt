package com.example.ui.screens

import android.content.ClipData
import android.content.ClipboardManager
import android.content.Context
import android.content.Intent
import android.widget.Toast
import androidx.compose.animation.*
import androidx.compose.animation.core.*
import androidx.compose.foundation.BorderStroke
import androidx.compose.foundation.background
import androidx.compose.foundation.layout.*
import androidx.compose.foundation.lazy.LazyRow
import androidx.compose.foundation.lazy.items
import androidx.compose.foundation.rememberScrollState
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.foundation.verticalScroll
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.*
import androidx.compose.material.icons.outlined.ContentCopy
import androidx.compose.material.icons.outlined.Share
import androidx.compose.material.icons.outlined.StarBorder
import androidx.compose.material3.*
import androidx.compose.runtime.*
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Brush
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.platform.LocalContext
import androidx.compose.ui.platform.testTag
import androidx.compose.ui.text.font.FontStyle
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.text.style.TextAlign
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import com.example.db.QuoteEntity
import com.example.ui.GenerateUiState
import com.example.ui.ModelsUiState
import com.example.ui.QuotAiViewModel
import com.example.ui.theme.*

@Composable
fun DashboardScreen(
    viewModel: QuotAiViewModel,
    modifier: Modifier = Modifier
) {
    val context = LocalContext.current
    val generateState by viewModel.generateState.collectAsState()
    val modelsState by viewModel.modelsState.collectAsState()
    val scrollState = rememberScrollState()

    val categories = listOf(
        "motivation" to "🔥 Motivation",
        "reflection" to "💭 Réflexion",
        "life" to "🌱 Vie",
        "focus" to "🎯 Focus",
        "sadness" to "😢 Tristesse",
        "dark" to "🌌 Sombre",
        "success" to "🏆 Réussite"
    )

    Column(
        modifier = modifier
            .fillMaxSize()
            .verticalScroll(scrollState)
            .padding(16.dp),
        horizontalAlignment = Alignment.CenterHorizontally
    ) {
        // Active GGUF model card status indicators
        ModelStatusIndicator(modelsState)

        Spacer(modifier = Modifier.height(16.dp))

        // Horizontal Category Selectors Slider
        Text(
            text = "Choisissez l'univers de votre citation :",
            color = MutedText,
            fontSize = 13.sp,
            fontWeight = FontWeight.SemiBold,
            modifier = Modifier.fillMaxWidth().padding(horizontal = 4.dp),
            textAlign = TextAlign.Start
        )

        Spacer(modifier = Modifier.height(8.dp))

        LazyRow(
            modifier = Modifier.fillMaxWidth(),
            horizontalArrangement = Arrangement.spacedBy(8.dp),
            contentPadding = PaddingValues(horizontal = 4.dp)
        ) {
            items(categories) { (id, label) ->
                val isSelected = generateState.category == id
                FilterChip(
                    selected = isSelected,
                    onClick = { viewModel.setCategory(id) },
                    label = { 
                        Text(
                            text = label, 
                            fontWeight = if (isSelected) FontWeight.Bold else FontWeight.Normal,
                            color = if (isSelected) SpaceBlack else Color.White
                        ) 
                    },
                    colors = FilterChipDefaults.filterChipColors(
                        selectedContainerColor = CyanTech,
                        containerColor = SpaceCard
                    ),
                    border = FilterChipDefaults.filterChipBorder(
                        enabled = true,
                        selected = isSelected,
                        borderColor = SurfaceBorder,
                        selectedBorderColor = CyanTech
                    ),
                    modifier = Modifier.testTag("chip_$id")
                )
            }
        }

        Spacer(modifier = Modifier.height(24.dp))

        // Main Glowed Quote Card View
        QuoteDisplayContainer(
            generateState = generateState,
            modelsState = modelsState,
            onFavoriteClick = { quote -> viewModel.toggleFavorite(quote) },
            onRegenSimilar = { text -> viewModel.generateQuote(isRegenSimilar = true, similarText = text) }
        )

        Spacer(modifier = Modifier.height(28.dp))

        // Big Primary Quote Generation Button
        Button(
            onClick = { viewModel.generateQuote() },
            enabled = modelsState.isModelLoaded && !generateState.isGenerating,
            colors = ButtonDefaults.buttonColors(
                containerColor = CyanTech,
                disabledContainerColor = DarkGrey,
                contentColor = SpaceBlack,
                disabledContentColor = MutedText
            ),
            shape = RoundedCornerShape(16.dp),
            modifier = Modifier
                .fillMaxWidth()
                .height(56.dp)
                .testTag("generate_quote_button")
        ) {
            val enabled = modelsState.isModelLoaded && !generateState.isGenerating
            Row(
                verticalAlignment = Alignment.CenterVertically,
                horizontalArrangement = Arrangement.Center
            ) {
                if (generateState.isGenerating) {
                    CircularProgressIndicator(
                        color = SpaceBlack,
                        strokeWidth = 3.dp,
                        modifier = Modifier.size(24.dp)
                    )
                    Spacer(modifier = Modifier.width(12.dp))
                    Text(
                        text = "GÉNÉRATION EN COURS...",
                        color = SpaceBlack,
                        fontWeight = FontWeight.Bold,
                        fontSize = 15.sp,
                        letterSpacing = 1.sp
                    )
                } else {
                    Icon(
                        imageVector = Icons.Default.Cyclone,
                        contentDescription = "Générer",
                        tint = if (enabled) SpaceBlack else MutedText
                    )
                    Spacer(modifier = Modifier.width(12.dp))
                    Text(
                        text = "GÉNÉRER AVEC L'IA LOCALE",
                        color = if (enabled) SpaceBlack else MutedText,
                        fontWeight = FontWeight.Bold,
                        fontSize = 14.sp,
                        letterSpacing = 0.5.sp
                    )
                }
            }
        }

        if (!modelsState.isModelLoaded) {
            Spacer(modifier = Modifier.height(12.dp))
            Row(
                verticalAlignment = Alignment.CenterVertically,
                horizontalArrangement = Arrangement.Center,
                modifier = Modifier.padding(horizontal = 16.dp)
            ) {
                Icon(
                    imageVector = Icons.Default.Warning,
                    contentDescription = "Warning",
                    tint = SoftGold,
                    modifier = Modifier.size(16.dp)
                )
                Spacer(modifier = Modifier.width(6.dp))
                Text(
                    text = "Veuillez charger un modèle .gguf dans l'onglet Configuration pour déverrouiller l'IA.",
                    textAlign = TextAlign.Center,
                    color = SoftGold,
                    fontSize = 12.sp
                )
            }
        }
    }
}

@Composable
fun ModelStatusIndicator(state: ModelsUiState) {
    Card(
        shape = RoundedCornerShape(12.dp),
        colors = CardDefaults.cardColors(containerColor = SpaceCard),
        border = BorderStroke(1.dp, SurfaceBorder),
        modifier = Modifier.fillMaxWidth()
    ) {
        Row(
            modifier = Modifier
                .fillMaxWidth()
                .padding(horizontal = 16.dp, vertical = 12.dp),
            verticalAlignment = Alignment.CenterVertically,
            horizontalArrangement = Arrangement.SpaceBetween
        ) {
            Row(verticalAlignment = Alignment.CenterVertically) {
                Box(
                    modifier = Modifier
                        .size(10.dp)
                        .background(
                            color = if (state.isModelLoaded) CyanTech else SoftRed,
                            shape = RoundedCornerShape(5.dp)
                        )
                )
                Spacer(modifier = Modifier.width(10.dp))
                Column {
                    Text(
                        text = if (state.isModelLoaded) "MÉMOIRE LLAMA CHARGÉE" else "AUCUN MODÈLE LOCAL",
                        fontSize = 10.sp,
                        fontWeight = FontWeight.Bold,
                        color = if (state.isModelLoaded) CyanTech else SoftRed
                    )
                    Text(
                        text = state.selectedModelName ?: "Sélectionnez un modèle .gguf",
                        fontSize = 14.sp,
                        fontWeight = FontWeight.Bold,
                        color = Color.White
                    )
                }
            }

            if (state.isModelLoaded) {
                SuggestionChip(
                    onClick = {},
                    label = { 
                        Text(
                            text = if (state.isLowMemoryMode) "Basse RAM" else "Standard RAM",
                            color = VelvetIndigo,
                            fontSize = 10.sp,
                            fontWeight = FontWeight.Bold
                        ) 
                    },
                    border = BorderStroke(1.dp, VelvetIndigo.copy(alpha = 0.5f)),
                    shape = RoundedCornerShape(8.dp)
                )
            }
        }
    }
}

@Composable
fun QuoteDisplayContainer(
    generateState: GenerateUiState,
    modelsState: ModelsUiState,
    onFavoriteClick: (QuoteEntity) -> Unit,
    onRegenSimilar: (String) -> Unit
) {
    val context = LocalContext.current
    
    // Pulse animation factor helper while generating
    val infiniteTransition = rememberInfiniteTransition()
    val pulseAlpha by infiniteTransition.animateFloat(
        initialValue = 0.4f,
        targetValue = 1.0f,
        animationSpec = infiniteRepeatable(
            animation = tween(1200, easing = LinearEasing),
            repeatMode = RepeatMode.Reverse
        )
    )

    Column(
        horizontalAlignment = Alignment.CenterHorizontally,
        modifier = Modifier.fillMaxWidth()
    ) {
        // Glow border styled box wrapper
        Card(
            shape = RoundedCornerShape(24.dp),
            border = BorderStroke(
                width = if (generateState.isGenerating) 2.dp else 1.dp,
                color = if (generateState.isGenerating) CyanTech.copy(alpha = pulseAlpha) else SurfaceBorder
            ),
            colors = CardDefaults.cardColors(containerColor = SpaceCard),
            modifier = Modifier
                .fillMaxWidth()
                .padding(vertical = 4.dp)
                .testTag("quote_rendered_card")
        ) {
            Column(
                modifier = Modifier
                    .fillMaxWidth()
                    .padding(24.dp),
                horizontalAlignment = Alignment.CenterHorizontally
            ) {
                // Display Texts with back-layered decorative quotes
                Box(
                    modifier = Modifier
                        .fillMaxWidth()
                        .padding(horizontal = 8.dp),
                    contentAlignment = Alignment.Center
                ) {
                    // Extremely subtle large serif quote background element for an elite editorial touch
                    Text(
                        text = "“",
                        fontFamily = androidx.compose.ui.text.font.FontFamily.Serif,
                        fontSize = 160.sp,
                        fontWeight = FontWeight.Bold,
                        color = Color.White.copy(alpha = 0.04f),
                        style = androidx.compose.ui.text.TextStyle(lineHeight = 1.sp),
                        modifier = Modifier
                            .align(Alignment.TopStart)
                            .offset(x = (-10).dp, y = (-70).dp)
                    )

                    if (generateState.text.isEmpty() && !generateState.isGenerating) {
                        Text(
                            text = "« Écrivez votre destin en chargeant un fichier GGUF et en pressant le bouton d'inférence. »",
                            color = LightGreyText,
                            fontSize = 19.sp,
                            fontFamily = androidx.compose.ui.text.font.FontFamily.Serif,
                            fontStyle = FontStyle.Italic,
                            textAlign = TextAlign.Center,
                            lineHeight = 28.sp,
                            modifier = Modifier.fillMaxWidth()
                        )
                    } else {
                        Text(
                            text = if (generateState.text.isNotEmpty()) "« ${generateState.text} »" else "Génération de la pensée...",
                            color = if (generateState.text.isNotEmpty()) Color.White else LightGreyText.copy(alpha = 0.7f),
                            fontSize = 20.sp,
                            fontFamily = androidx.compose.ui.text.font.FontFamily.Serif,
                            fontWeight = FontWeight.Medium,
                            fontStyle = FontStyle.Italic,
                            textAlign = TextAlign.Center,
                            lineHeight = 30.sp,
                            modifier = Modifier.fillMaxWidth()
                        )
                    }
                }

                Spacer(modifier = Modifier.height(20.dp))

                // Meta category tag + Source Model ID Info
                if (generateState.text.isNotEmpty() || generateState.isGenerating) {
                    Row(
                        modifier = Modifier.fillMaxWidth(),
                        horizontalArrangement = Arrangement.SpaceBetween,
                        verticalAlignment = Alignment.CenterVertically
                    ) {
                        // Category pill
                        Surface(
                            color = VelvetIndigo.copy(alpha = 0.15f),
                            shape = RoundedCornerShape(8.dp),
                            border = BorderStroke(1.dp, VelvetIndigo.copy(alpha = 0.3f))
                        ) {
                            Text(
                                text = generateState.category.uppercase(),
                                color = VelvetIndigo,
                                fontSize = 10.sp,
                                fontWeight = FontWeight.Bold,
                                modifier = Modifier.padding(horizontal = 8.dp, vertical = 4.dp)
                            )
                        }

                        // Local Telemetry Display
                        Text(
                            text = "⏱️ ${generateState.elapsedSeconds}s | ⚡ ${generateState.speedTokensSec} t/s",
                            color = MutedText,
                            fontSize = 11.sp,
                            fontWeight = FontWeight.Medium
                        )
                    }
                }
            }
        }

        generateState.error?.let { err ->
            Spacer(modifier = Modifier.height(12.dp))
            Text(
                text = err,
                color = SoftRed,
                fontSize = 13.sp,
                textAlign = TextAlign.Center,
                fontWeight = FontWeight.SemiBold,
                modifier = Modifier.padding(horizontal = 8.dp)
            )
        }

        // Action Toolbar
        if (generateState.text.isNotEmpty() && !generateState.isGenerating) {
            Spacer(modifier = Modifier.height(16.dp))
            Row(
                modifier = Modifier.fillMaxWidth(),
                horizontalArrangement = Arrangement.SpaceEvenly,
                verticalAlignment = Alignment.CenterVertically
            ) {
                // Clipboard copy button
                IconButton(
                    onClick = {
                        val clipboard = context.getSystemService(Context.CLIPBOARD_SERVICE) as ClipboardManager
                        val clip = ClipData.newPlainText("QuotAI", generateState.text)
                        clipboard.setPrimaryClip(clip)
                        Toast.makeText(context, "Citation copiée dans le presse-papiers !", Toast.LENGTH_SHORT).show()
                    },
                    modifier = Modifier.testTag("copy_button")
                ) {
                    Column(horizontalAlignment = Alignment.CenterHorizontally) {
                        Icon(imageVector = Icons.Outlined.ContentCopy, contentDescription = "Copier", tint = LightGreyText)
                        Text(text = "Copier", fontSize = 9.sp, color = MutedText)
                    }
                }

                // Native Share Intent Button
                IconButton(
                    onClick = {
                        val shareIntent = Intent().apply {
                            action = Intent.ACTION_SEND
                            putExtra(Intent.EXTRA_TEXT, "« ${generateState.text} » — Généré hors-ligne par QuotAI (${modelsState.selectedModelName})")
                            type = "text/plain"
                        }
                        context.startActivity(Intent.createChooser(shareIntent, "Partager via"))
                    },
                    modifier = Modifier.testTag("share_button")
                ) {
                    Column(horizontalAlignment = Alignment.CenterHorizontally) {
                        Icon(imageVector = Icons.Outlined.Share, contentDescription = "Partager", tint = LightGreyText)
                        Text(text = "Partager", fontSize = 9.sp, color = MutedText)
                    }
                }

                // Favorite Toggle Star
                val isFavorite = generateState.lastGeneratedQuote?.isFavorite == true
                IconButton(
                    onClick = { generateState.lastGeneratedQuote?.let { onFavoriteClick(it) } },
                    enabled = generateState.lastGeneratedQuote != null,
                    modifier = Modifier.testTag("favorite_toggle_button")
                ) {
                    Column(horizontalAlignment = Alignment.CenterHorizontally) {
                        Icon(
                            imageVector = if (isFavorite) Icons.Filled.Star else Icons.Outlined.StarBorder,
                            contentDescription = "Favori",
                            tint = if (isFavorite) SoftGold else LightGreyText
                        )
                        Text(text = "Favori", fontSize = 9.sp, color = MutedText)
                    }
                }

                // Rewrite / Regen similar button (Advanced feature!)
                IconButton(
                    onClick = { onRegenSimilar(generateState.text) },
                    modifier = Modifier.testTag("rewrite_similar_button")
                ) {
                    Column(horizontalAlignment = Alignment.CenterHorizontally) {
                        Icon(imageVector = Icons.Default.Brush, contentDescription = "Réécrire", tint = LightGreyText)
                        Text(text = "Similaire", fontSize = 9.sp, color = MutedText)
                    }
                }
            }
        }
    }
}
