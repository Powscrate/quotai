package com.example.db

import androidx.room.*
import kotlinx.coroutines.flow.Flow

@Dao
interface QuoteDao {
    @Query("SELECT * FROM quotes ORDER BY timestamp DESC")
    fun getAllQuotesFlow(): Flow<List<QuoteEntity>>

    @Query("SELECT * FROM quotes WHERE isFavorite = 1 ORDER BY timestamp DESC")
    fun getFavoritesFlow(): Flow<List<QuoteEntity>>

    @Query("SELECT * FROM quotes ORDER BY timestamp DESC LIMIT 1")
    suspend fun getLatestQuote(): QuoteEntity?

    @Query("SELECT * FROM quotes WHERE category = :category ORDER BY timestamp DESC")
    fun getQuotesByCategoryFlow(category: String): Flow<List<QuoteEntity>>

    @Insert(onConflict = OnConflictStrategy.REPLACE)
    suspend fun insertQuote(quote: QuoteEntity): Long

    @Update
    suspend fun updateQuote(quote: QuoteEntity)

    @Query("DELETE FROM quotes WHERE id = :id")
    suspend fun deleteQuoteById(id: Long)

    @Query("DELETE FROM quotes")
    suspend fun clearHistory()
}
