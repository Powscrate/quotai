package com.example.ui.screens

import android.content.ClipData
import android.content.ClipboardManager
import android.content.Context
import android.content.Intent
import android.widget.Toast
import androidx.compose.animation.*
import androidx.compose.foundation.BorderStroke
import androidx.compose.foundation.background
import androidx.compose.foundation.layout.*
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.lazy.items
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.*
import androidx.compose.material.icons.outlined.ContentCopy
import androidx.compose.material.icons.outlined.Delete
import androidx.compose.material.icons.outlined.Share
import androidx.compose.material.icons.outlined.Star
import androidx.compose.material3.*
import androidx.compose.material3.TabRowDefaults.tabIndicatorOffset
import androidx.compose.runtime.*
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.platform.LocalContext
import androidx.compose.ui.platform.testTag
import androidx.compose.ui.text.font.FontStyle
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.text.style.TextAlign
import androidx.compose.ui.text.style.TextOverflow
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import com.example.db.QuoteEntity
import com.example.ui.QuotAiViewModel
import com.example.ui.theme.*
import java.text.SimpleDateFormat
import java.util.*

@Composable
fun HistoryScreen(
    viewModel: QuotAiViewModel,
    modifier: Modifier = Modifier
) {
    var selectedSubTab by remember { mutableStateOf(0) } // 0 = History, 1 = Favorites
    val quotesList by viewModel.allQuotes.collectAsState()
    val favoritesList by viewModel.favoriteQuotes.collectAsState()
    var searchQuery by remember { mutableStateOf("") }
    var showDeleteConfirm by remember { mutableStateOf(false) }

    val activeList = if (selectedSubTab == 0) quotesList else favoritesList
    val filteredList = remember(activeList, searchQuery) {
        if (searchQuery.isBlank()) {
            activeList
        } else {
            activeList.filter { 
                it.text.contains(searchQuery, ignoreCase = true) || 
                it.category.contains(searchQuery, ignoreCase = true) ||
                it.sourceModel.contains(searchQuery, ignoreCase = true)
            }
        }
    }

    Column(
        modifier = modifier
            .fillMaxSize()
            .padding(16.dp),
        horizontalAlignment = Alignment.CenterHorizontally
    ) {
        // Sub-Tab Switcher
        TabRow(
            selectedTabIndex = selectedSubTab,
            containerColor = SpaceBlack,
            contentColor = CyanTech,
            divider = { HorizontalDivider(color = SurfaceBorder) },
            indicator = { tabPositions ->
                TabRowDefaults.SecondaryIndicator(
                    modifier = Modifier.tabIndicatorOffset(tabPositions[selectedSubTab]),
                    color = CyanTech
                )
            }
        ) {
            Tab(
                selected = selectedSubTab == 0,
                onClick = { selectedSubTab = 0 },
                text = { 
                    Row(verticalAlignment = Alignment.CenterVertically) {
                        Icon(imageVector = Icons.Default.History, contentDescription = null, modifier = Modifier.size(16.dp))
                        Spacer(modifier = Modifier.width(6.dp))
                        Text("Archive History", fontWeight = FontWeight.SemiBold)
                    }
                },
                modifier = Modifier.testTag("tab_history")
            )
            Tab(
                selected = selectedSubTab == 1,
                onClick = { selectedSubTab = 1 },
                text = { 
                    Row(verticalAlignment = Alignment.CenterVertically) {
                        Icon(imageVector = Icons.Default.Star, contentDescription = null, modifier = Modifier.size(16.dp))
                        Spacer(modifier = Modifier.width(6.dp))
                        Text("Favorites", fontWeight = FontWeight.SemiBold)
                    }
                },
                modifier = Modifier.testTag("tab_favorites")
            )
        }

        Spacer(modifier = Modifier.height(16.dp))

        // Search Bar & Clear all control row
        Row(
            modifier = Modifier.fillMaxWidth(),
            verticalAlignment = Alignment.CenterVertically
        ) {
            TextField(
                value = searchQuery,
                onValueChange = { searchQuery = it },
                placeholder = { Text("Rechercher une pensée...", color = MutedText, fontSize = 14.sp) },
                leadingIcon = { Icon(imageVector = Icons.Default.Search, contentDescription = null, tint = MutedText) },
                trailingIcon = {
                    if (searchQuery.isNotEmpty()) {
                        IconButton(onClick = { searchQuery = "" }) {
                            Icon(imageVector = Icons.Default.Close, contentDescription = "Effacer", tint = MutedText)
                        }
                    }
                },
                colors = TextFieldDefaults.colors(
                    focusedTextColor = Color.White,
                    unfocusedTextColor = Color.White,
                    focusedContainerColor = SpaceCard,
                    unfocusedContainerColor = SpaceCard,
                    focusedIndicatorColor = Color.Transparent,
                    unfocusedIndicatorColor = Color.Transparent,
                    disabledIndicatorColor = Color.Transparent
                ),
                shape = RoundedCornerShape(12.dp),
                modifier = Modifier
                    .weight(1f)
                    .height(52.dp)
                    .testTag("search_bar")
            )

            if (selectedSubTab == 0 && quotesList.isNotEmpty()) {
                Spacer(modifier = Modifier.width(8.dp))
                IconButton(
                    onClick = { showDeleteConfirm = true },
                    modifier = Modifier
                        .size(52.dp)
                        .background(DarkGrey, shape = RoundedCornerShape(12.dp))
                        .testTag("purge_button")
                ) {
                    Icon(imageVector = Icons.Outlined.Delete, contentDescription = "Purger l'historique", tint = SoftRed)
                }
            }
        }

        Spacer(modifier = Modifier.height(16.dp))

        // Data lists
        if (filteredList.isEmpty()) {
            EmptyListPlaceholder(searchQuery, selectedSubTab)
        } else {
            LazyColumn(
                verticalArrangement = Arrangement.spacedBy(12.dp),
                modifier = Modifier.fillMaxWidth()
            ) {
                items(filteredList, key = { it.id }) { quote ->
                    QuoteListItem(
                        quote = quote,
                        onToggleFavorite = { viewModel.toggleFavorite(quote) },
                        onDelete = { viewModel.deleteQuote(quote.id) }
                    )
                }
            }
        }
    }

    // Confirmation purget dialog logic
    if (showDeleteConfirm) {
        AlertDialog(
            onDismissRequest = { showDeleteConfirm = false },
            title = { Text("Purger l'historique ?", fontWeight = FontWeight.Bold) },
            text = { Text("Cette action supprimera définitivement toutes les citations stockées dans votre appareil. Les favoris seront également effacés.") },
            confirmButton = {
                Button(
                    onClick = {
                        viewModel.clearHistory()
                        showDeleteConfirm = false
                    },
                    colors = ButtonDefaults.buttonColors(containerColor = SoftRed)
                ) {
                    Text("Tout supprimer", color = Color.White, fontWeight = FontWeight.Bold)
                }
            },
            dismissButton = {
                TextButton(onClick = { showDeleteConfirm = false }) {
                    Text("Annuler", color = Color.Gray)
                }
            },
            containerColor = SpaceCard,
            textContentColor = LightGreyText,
            titleContentColor = Color.White
        )
    }
}

@Composable
fun QuoteListItem(
    quote: QuoteEntity,
    onToggleFavorite: () -> Unit,
    onDelete: () -> Unit
) {
    val context = LocalContext.current
    val sdf = SimpleDateFormat("dd MMM yyyy, HH:mm", Locale.FRANCE)
    val formattedDate = sdf.format(Date(quote.timestamp))

    Card(
        shape = RoundedCornerShape(16.dp),
        colors = CardDefaults.cardColors(containerColor = SpaceCard),
        border = BorderStroke(1.dp, SurfaceBorder),
        modifier = Modifier
            .fillMaxWidth()
            .testTag("quote_list_item_${quote.id}")
    ) {
        Column(
            modifier = Modifier
                .fillMaxWidth()
                .padding(16.dp)
        ) {
            // Main text italics in Serif for consistent editorial styling
            Text(
                text = "« ${quote.text} »",
                color = Color.White,
                fontSize = 16.sp,
                fontFamily = androidx.compose.ui.text.font.FontFamily.Serif,
                fontStyle = FontStyle.Italic,
                fontWeight = FontWeight.Medium,
                modifier = Modifier.fillMaxWidth()
            )

            Spacer(modifier = Modifier.height(12.dp))

            // Sub info lines: model used + category + date
            Row(
                modifier = Modifier.fillMaxWidth(),
                verticalAlignment = Alignment.CenterVertically,
                horizontalArrangement = Arrangement.SpaceBetween
            ) {
                // Left badge categoriser
                Row(verticalAlignment = Alignment.CenterVertically) {
                    Surface(
                        color = VelvetIndigo.copy(alpha = 0.15f),
                        shape = RoundedCornerShape(6.dp),
                        border = BorderStroke(1.dp, VelvetIndigo.copy(alpha = 0.2f))
                    ) {
                        Text(
                            text = quote.category.uppercase(),
                            color = VelvetIndigo,
                            fontSize = 8.sp,
                            fontWeight = FontWeight.Bold,
                            modifier = Modifier.padding(horizontal = 6.dp, vertical = 2.dp)
                        )
                    }
                    Spacer(modifier = Modifier.width(6.dp))
                    Text(
                        text = quote.sourceModel,
                        color = MutedText,
                        fontSize = 10.sp,
                        fontWeight = FontWeight.Medium,
                        maxLines = 1,
                        overflow = TextOverflow.Ellipsis,
                        modifier = Modifier.widthIn(max = 100.dp)
                    )
                }

                // Right date tag
                Text(
                    text = formattedDate,
                    color = MutedText,
                    fontSize = 10.sp
                )
            }

            HorizontalDivider(color = SurfaceBorder, modifier = Modifier.padding(vertical = 12.dp))

            // Lower toolbars action triggers
            Row(
                modifier = Modifier.fillMaxWidth(),
                horizontalArrangement = Arrangement.End,
                verticalAlignment = Alignment.CenterVertically
            ) {
                IconButton(
                    onClick = {
                        val clipboard = context.getSystemService(Context.CLIPBOARD_SERVICE) as ClipboardManager
                        val clip = ClipData.newPlainText("QuotAI", quote.text)
                        clipboard.setPrimaryClip(clip)
                        Toast.makeText(context, "Citation copiée !", Toast.LENGTH_SHORT).show()
                    },
                    modifier = Modifier.size(36.dp)
                ) {
                    Icon(imageVector = Icons.Outlined.ContentCopy, contentDescription = "Copier", tint = LightGreyText, modifier = Modifier.size(18.dp))
                }

                Spacer(modifier = Modifier.width(8.dp))

                IconButton(
                    onClick = {
                        val shareIntent = Intent().apply {
                            action = Intent.ACTION_SEND
                            putExtra(Intent.EXTRA_TEXT, "« ${quote.text} » — Généré par l'IA offline QuotAI")
                            type = "text/plain"
                        }
                        context.startActivity(Intent.createChooser(shareIntent, "Partager"))
                    },
                    modifier = Modifier.size(36.dp)
                ) {
                    Icon(imageVector = Icons.Outlined.Share, contentDescription = "Partager", tint = LightGreyText, modifier = Modifier.size(18.dp))
                }

                Spacer(modifier = Modifier.width(16.dp))

                IconButton(
                    onClick = onToggleFavorite,
                    modifier = Modifier.size(36.dp)
                ) {
                    Icon(
                        imageVector = if (quote.isFavorite) Icons.Filled.Star else Icons.Default.StarOutline,
                        contentDescription = "Favori",
                        tint = if (quote.isFavorite) SoftGold else LightGreyText,
                        modifier = Modifier.size(20.dp)
                    )
                }

                Spacer(modifier = Modifier.width(8.dp))

                IconButton(
                    onClick = onDelete,
                    modifier = Modifier.size(36.dp)
                ) {
                    Icon(imageVector = Icons.Default.DeleteSweep, contentDescription = "Supprimer", tint = SoftRed, modifier = Modifier.size(20.dp))
                }
            }
        }
    }
}

@Composable
fun EmptyListPlaceholder(searchQuery: String, tabIndex: Int) {
    Column(
        modifier = Modifier
            .fillMaxSize()
            .padding(24.dp),
        verticalArrangement = Arrangement.Center,
        horizontalAlignment = Alignment.CenterHorizontally
    ) {
        Icon(
            imageVector = if (searchQuery.isNotEmpty()) Icons.Default.SearchOff else if (tabIndex == 0) Icons.Default.Receipt else Icons.Default.AutoAwesome,
            contentDescription = null,
            tint = MutedText.copy(alpha = 0.3f),
            modifier = Modifier.size(64.dp)
        )
        Spacer(modifier = Modifier.height(16.dp))
        Text(
            text = if (searchQuery.isNotEmpty()) {
                "Aucun résultat pour \"$searchQuery\""
            } else if (tabIndex == 0) {
                "Votre historique d'inférence est vierge."
            } else {
                "Aucun coup de cœur pour l'instant !"
            },
            color = LightGreyText,
            fontSize = 15.sp,
            fontWeight = FontWeight.SemiBold,
            textAlign = TextAlign.Center
        )
        Spacer(modifier = Modifier.height(6.dp))
        Text(
            text = if (searchQuery.isNotEmpty()) {
                "Essayez d'autres mots-clés ou modifiez votre recherche."
            } else if (tabIndex == 0) {
                "Générez une citation dans l'onglet principal et elle apparaîtra archivée ici."
            } else {
                "Pressez l'étoile dorée sous une citation générée pour la sauvegarder."
            },
            color = MutedText,
            fontSize = 12.sp,
            textAlign = TextAlign.Center,
            modifier = Modifier.padding(horizontal = 16.dp)
        )
    }
}
