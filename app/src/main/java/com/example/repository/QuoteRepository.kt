package com.example.repository

import com.example.db.QuoteDao
import com.example.db.QuoteEntity
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.flow.Flow
import kotlinx.coroutines.withContext

class QuoteRepository(private val quoteDao: QuoteDao) {

    val allQuotes: Flow<List<QuoteEntity>> = quoteDao.getAllQuotesFlow()
    val favoriteQuotes: Flow<List<QuoteEntity>> = quoteDao.getFavoritesFlow()

    fun getQuotesByCategory(category: String): Flow<List<QuoteEntity>> {
        return quoteDao.getQuotesByCategoryFlow(category)
    }

    suspend fun getLatestQuote(): QuoteEntity? = withContext(Dispatchers.IO) {
        return@withContext quoteDao.getLatestQuote()
    }

    suspend fun saveGeneratedQuote(text: String, modelName: String, categoryOverride: String? = null): QuoteEntity = withContext(Dispatchers.IO) {
        val category = categoryOverride ?: autoCategorizeFrenchText(text)
        val newQuote = QuoteEntity(
            text = text,
            category = category,
            timestamp = System.currentTimeMillis(),
            sourceModel = modelName,
            isFavorite = false
        )
        val id = quoteDao.insertQuote(newQuote)
        return@withContext newQuote.copy(id = id)
    }

    suspend fun toggleFavorite(quote: QuoteEntity): QuoteEntity = withContext(Dispatchers.IO) {
        val updated = quote.copy(isFavorite = !quote.isFavorite)
        quoteDao.updateQuote(updated)
        return@withContext updated
    }

    suspend fun deleteQuote(id: Long) = withContext(Dispatchers.IO) {
        quoteDao.deleteQuoteById(id)
    }

    suspend fun clearAllHistory() = withContext(Dispatchers.IO) {
        quoteDao.clearHistory()
    }

    /**
     * Highly optimized, linguistic classification algorithms mapping key French semantics
     * to M3 categories. Light, fast, runs perfectly on 1GB RAM budget.
     */
    fun autoCategorizeFrenchText(text: String): String {
        val t = text.lowercase()
        return when {
            // SUCCESS
            t.contains("succès") || t.contains("réuss") || t.contains("triomphe") ||
            t.contains("gagner") || t.contains("sommet") || t.contains("victoire") ||
            t.contains("gloire") || t.contains("excellence") || t.contains("conqu") -> "success"

            // SADNESS
            t.contains("triste") || t.contains("larme") || t.contains("pleur") ||
            t.contains("mélancol") || t.contains("chagrin") || t.contains("peine") ||
            t.contains("regret") || t.contains("blessure") || t.contains("douleur") -> "sadness"

            // DARK
            t.contains("sombre") || t.contains("ténèbr") || t.contains("obscur") ||
            t.contains("abîme") || t.contains("désespoir") || t.contains("monstre") ||
            t.contains("pacte") || t.contains("vide") || t.contains("nuit") ||
            t.contains("mort") || t.contains("froid") -> "dark"

            // MOTIVATION
            t.contains("force") || t.contains("courage") || t.contains("persévér") ||
            t.contains("obstacle") || t.contains("continuer") || t.contains("lutter") ||
            t.contains("acier") || t.contains("lever") || t.contains("fort") ||
            t.contains("discipline") || t.contains("audace") || t.contains("volonté") -> "motivation"

            // FOCUS
            t.contains("attention") || t.contains("concentr") || t.contains("clarté") ||
            t.contains("essentiel") || t.contains("laser") || t.contains("élagu") ||
            t.contains("superflu") || t.contains("faisceau") || t.contains("calmer") ||
            t.contains("ancre") || t.contains("silence") -> "focus"

            // LIFE
            t.contains("vie") || t.contains("vivre") || t.contains("chemin") ||
            t.contains("monde") || t.contains("art") || t.contains("destin") ||
            t.contains("fleuve") || t.contains("compromis") || t.contains("exister") -> "life"

            // REFLECTION (Catch-all fallback representing thought expression structure)
            t.contains("pens") || t.contains("réflex") || t.contains("sagesse") ||
            t.contains("miroir") || t.contains("lucide") || t.contains("vérité") ||
            t.contains("âme") || t.contains("temps") || t.contains("connaître") ||
            t.contains("philosoph") || t.contains("lucidité") -> "reflection"

            else -> "reflection" // Safe default
        }
    }
}
