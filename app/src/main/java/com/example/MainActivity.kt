package com.example

import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.activity.viewModels
import androidx.compose.foundation.background
import androidx.compose.foundation.border
import androidx.compose.foundation.layout.*
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.AutoAwesome
import androidx.compose.material.icons.filled.History
import androidx.compose.material.icons.filled.Settings
import androidx.compose.material.icons.outlined.AutoAwesome
import androidx.compose.material.icons.outlined.History
import androidx.compose.material.icons.outlined.Settings
import androidx.compose.material3.*
import androidx.compose.runtime.*
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import com.example.ui.QuotAiViewModel
import com.example.ui.screens.DashboardScreen
import com.example.ui.screens.HistoryScreen
import com.example.ui.screens.ModelScreen
import com.example.ui.theme.CyanTech
import com.example.ui.theme.MyApplicationTheme
import com.example.ui.theme.SpaceBlack
import com.example.ui.theme.SpaceCard
import com.example.ui.theme.VelvetIndigo
import com.example.ui.theme.SurfaceBorder
import com.example.ui.theme.MutedText

class MainActivity : ComponentActivity() {

    private val viewModel: QuotAiViewModel by viewModels()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        
        // Enable true edge-to-edge
        enableEdgeToEdge()

        setContent {
            MyApplicationTheme {
                var currentScreen by remember { mutableStateOf(0) } // 0 = Gen, 1 = History/Prefs, 2 = Config

                Scaffold(
                    modifier = Modifier.fillMaxSize(),
                    topBar = {
                        Column {
                            // Status bar spacer
                            Spacer(
                                modifier = Modifier
                                    .fillMaxWidth()
                                    .windowInsetsTopHeight(WindowInsets.statusBars)
                                    .background(SpaceBlack)
                            )
                            CustomTopAppBar(selectedTab = currentScreen, viewModel = viewModel)
                        }
                    },
                    bottomBar = {
                        CustomBottomNavigationBar(
                            selectedTab = currentScreen,
                            onTabSelected = { currentScreen = it }
                        )
                    },
                    containerColor = SpaceBlack
                ) { innerPadding ->
                    Box(
                        modifier = Modifier
                            .fillMaxSize()
                            .padding(innerPadding)
                            .background(SpaceBlack)
                    ) {
                        when (currentScreen) {
                            0 -> DashboardScreen(viewModel = viewModel)
                            1 -> HistoryScreen(viewModel = viewModel)
                            2 -> ModelScreen(viewModel = viewModel)
                        }
                    }
                }
            }
        }
    }
}

@Composable
fun CustomTopAppBar(selectedTab: Int, viewModel: QuotAiViewModel) {
    val modelsState by viewModel.modelsState.collectAsState()
    
    val screenTitle = when (selectedTab) {
        0 -> "Dashboard"
        1 -> "Mes Citations"
        else -> "Configuration"
    }

    Surface(
        color = SpaceBlack,
        tonalElevation = 0.dp
    ) {
        Column {
            Row(
                modifier = Modifier
                    .fillMaxWidth()
                    .height(64.dp)
                    .padding(horizontal = 24.dp),
                verticalAlignment = Alignment.CenterVertically,
                horizontalArrangement = Arrangement.SpaceBetween
            ) {
                Column {
                    Text(
                        text = "QUOTAI v1.2",
                        color = CyanTech,
                        fontSize = 10.sp,
                        fontWeight = FontWeight.Bold,
                        letterSpacing = 1.5.sp
                    )
                    Spacer(modifier = Modifier.height(2.dp))
                    Text(
                        text = screenTitle,
                        color = Color.White,
                        fontSize = 20.sp,
                        fontWeight = FontWeight.Medium,
                        letterSpacing = (-0.5).sp
                    )
                }

                // Dynamic Model Badge Status
                val modelName = modelsState.selectedModelName ?: "hors-ligne"
                val displayModel = if (modelName.lowercase().endsWith(".gguf")) {
                    modelName
                } else if (modelsState.isModelLoaded) {
                    modelName
                } else {
                    "hors-ligne"
                }

                Row(
                    verticalAlignment = Alignment.CenterVertically,
                    modifier = Modifier
                        .background(color = SpaceCard, shape = RoundedCornerShape(50.dp))
                        .border(width = 1.dp, color = SurfaceBorder, shape = RoundedCornerShape(50.dp))
                        .padding(horizontal = 12.dp, vertical = 6.dp)
                ) {
                    Box(
                        modifier = Modifier
                            .size(7.dp)
                            .background(
                                color = if (modelsState.isModelLoaded) Color(0xFF4ADE80) else Color(0xFF938F99),
                                shape = RoundedCornerShape(50.dp)
                            )
                    )
                    Spacer(modifier = Modifier.width(8.dp))
                    Text(
                        text = displayModel,
                        color = MutedText,
                        fontSize = 11.sp,
                        fontFamily = androidx.compose.ui.text.font.FontFamily.Monospace,
                        fontWeight = FontWeight.Medium
                    )
                }
            }
            HorizontalDivider(color = SurfaceBorder, thickness = 1.dp)
        }
    }
}

@Composable
fun CustomBottomNavigationBar(
    selectedTab: Int,
    onTabSelected: (Int) -> Unit
) {
    Column {
        HorizontalDivider(color = SurfaceBorder, thickness = 1.dp)
        NavigationBar(
            containerColor = Color(0xFF211F26),
            tonalElevation = 0.dp,
            windowInsets = WindowInsets.navigationBars, // Prevents navigation overlaps
            modifier = Modifier.height(84.dp)
        ) {
            NavigationBarItem(
                selected = selectedTab == 0,
                onClick = { onTabSelected(0) },
                label = { Text("Génération", fontSize = 11.sp, fontWeight = FontWeight.Bold) },
                icon = {
                    Icon(
                        imageVector = if (selectedTab == 0) Icons.Filled.AutoAwesome else Icons.Outlined.AutoAwesome,
                        contentDescription = "Génération"
                    )
                },
                colors = NavigationBarItemDefaults.colors(
                    selectedIconColor = SpaceBlack,
                    selectedTextColor = CyanTech,
                    indicatorColor = VelvetIndigo,
                    unselectedIconColor = Color.Gray,
                    unselectedTextColor = Color.Gray
                )
            )

            NavigationBarItem(
                selected = selectedTab == 1,
                onClick = { onTabSelected(1) },
                label = { Text("Mes Citations", fontSize = 11.sp, fontWeight = FontWeight.Bold) },
                icon = {
                    Icon(
                        imageVector = if (selectedTab == 1) Icons.Filled.History else Icons.Outlined.History,
                        contentDescription = "Mes Citations"
                    )
                },
                colors = NavigationBarItemDefaults.colors(
                    selectedIconColor = SpaceBlack,
                    selectedTextColor = CyanTech,
                    indicatorColor = VelvetIndigo,
                    unselectedIconColor = Color.Gray,
                    unselectedTextColor = Color.Gray
                )
            )

            NavigationBarItem(
                selected = selectedTab == 2,
                onClick = { onTabSelected(2) },
                label = { Text("Configuration", fontSize = 11.sp, fontWeight = FontWeight.Bold) },
                icon = {
                    Icon(
                        imageVector = if (selectedTab == 2) Icons.Filled.Settings else Icons.Outlined.Settings,
                        contentDescription = "Configuration"
                    )
                },
                colors = NavigationBarItemDefaults.colors(
                    selectedIconColor = SpaceBlack,
                    selectedTextColor = CyanTech,
                    indicatorColor = VelvetIndigo,
                    unselectedIconColor = Color.Gray,
                    unselectedTextColor = Color.Gray
                )
            )
        }
    }
}

