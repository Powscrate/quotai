package com.example.db

import androidx.room.Entity
import androidx.room.PrimaryKey
import java.io.Serializable

@Entity(tableName = "quotes")
data class QuoteEntity(
    @PrimaryKey(autoGenerate = true) val id: Long = 0,
    val text: String,
    val category: String,
    val timestamp: Long = System.currentTimeMillis(),
    val sourceModel: String,
    val isFavorite: Boolean = false
) : Serializable
