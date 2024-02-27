package ru.rustore.unitysdk.pushclient.model

import android.net.Uri

data class PushNotification(
    val title: String?,
    val body: String?,
    val channelId: String?,
    val imageUrl: Uri?,
    val color: String?,
    val icon: String?,
    val clickAction: String?
)
