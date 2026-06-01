package com.example.ui.theme

import android.os.Build
import androidx.compose.foundation.isSystemInDarkTheme
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.darkColorScheme
import androidx.compose.material3.dynamicDarkColorScheme
import androidx.compose.runtime.Composable
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.platform.LocalContext

private val QuotAiDarkColorScheme = darkColorScheme(
    primary = CyanTech,
    onPrimary = Color(0xFF381E72),
    primaryContainer = TealAccent,
    onPrimaryContainer = Color(0xFFEADBFF),
    secondary = VelvetIndigo,
    onSecondary = Color(0xFF1D192B),
    secondaryContainer = Color(0xFF49454F),
    onSecondaryContainer = Color(0xFFE8DEF8),
    tertiary = SoftGold,
    onTertiary = Color(0xFF422E00),
    surface = SpaceCard,
    onSurface = Color.White,
    background = SpaceBlack,
    onBackground = Color(0xFFECEFF1),
    error = SoftRed,
    onError = Color(0xFF601410)
)

@Composable
fun MyApplicationTheme(
    darkTheme: Boolean = true, // Force Dark mode by default for that premium offline AI console feel!
    dynamicColor: Boolean = false, // Use our custom color palette to preserve brand identity
    content: @Composable () -> Unit
) {
    val colorScheme = when {
        dynamicColor && Build.VERSION.SDK_INT >= Build.VERSION_CODES.S -> {
            val context = LocalContext.current
            dynamicDarkColorScheme(context)
        }
        else -> QuotAiDarkColorScheme
    }

    MaterialTheme(
        colorScheme = colorScheme,
        typography = Typography,
        content = content
    )
}
