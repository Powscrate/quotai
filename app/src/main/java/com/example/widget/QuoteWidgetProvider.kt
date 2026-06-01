package com.example.widget

import android.app.PendingIntent
import android.appwidget.AppWidgetManager
import android.appwidget.AppWidgetProvider
import android.content.Context
import android.content.Intent
import android.widget.RemoteViews
import com.example.MainActivity
import com.example.R
import com.example.db.QuoteDatabase
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.launch

class QuoteWidgetProvider : AppWidgetProvider() {

    override fun onUpdate(
        context: Context,
        appWidgetManager: AppWidgetManager,
        appWidgetIds: IntArray
    ) {
        val database = QuoteDatabase.getDatabase(context)
        
        // Launch in IO coroutine dispatcher to completely prevent blocking the main thread
        CoroutineScope(Dispatchers.IO).launch {
            val latestQuote = database.quoteDao().getLatestQuote()
            val text = latestQuote?.text ?: "Générez votre première pensée inspirante !"
            val category = latestQuote?.category?.uppercase() ?: "HORS-LIGNE"
            
            for (appWidgetId in appWidgetIds) {
                val views = RemoteViews(context.packageName, R.layout.quote_widget)
                
                // Bind values
                views.setTextViewText(R.id.widget_title, "QuotAI • $category")
                views.setTextViewText(R.id.widget_quote_text, "« $text »")
                
                // Register launch padding intent on widget clicks
                val intent = Intent(context, MainActivity::class.java).apply {
                    flags = Intent.FLAG_ACTIVITY_NEW_TASK or Intent.FLAG_ACTIVITY_CLEAR_TASK
                }
                
                val pendingIntent = PendingIntent.getActivity(
                    context,
                    0,
                    intent,
                    PendingIntent.FLAG_UPDATE_CURRENT or PendingIntent.FLAG_IMMUTABLE
                )
                
                // Bind touch targets
                views.setOnClickPendingIntent(R.id.widget_quote_text, pendingIntent)
                views.setOnClickPendingIntent(R.id.widget_title, pendingIntent)
                
                appWidgetManager.updateAppWidget(appWidgetId, views)
            }
        }
    }
}
