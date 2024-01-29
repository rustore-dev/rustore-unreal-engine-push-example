package ru.rustore.unitysdk.pushclient.model

import ru.rustore.sdk.pushclient.messaging.model.Notification
import ru.rustore.sdk.pushclient.messaging.model.RemoteMessage

object PushConverter {
    @JvmStatic
    fun Convert(remoteMessage: RemoteMessage): PushMessage {
        return PushMessage(
            messageId = remoteMessage.messageId,
            priority = remoteMessage.priority,
            ttl = remoteMessage.ttl,
            collapseKey = remoteMessage.collapseKey,
            data = remoteMessage.data,
            rawData = remoteMessage.rawData,
            notification = Convert(remoteMessage.notification)
        )
    }

    @JvmStatic
    fun Convert(pushNotification: Notification?): PushNotification? {
        return when (pushNotification) {
            null -> null
            else -> PushNotification(
                title = pushNotification.title,
                body = pushNotification.body,
                channelId = pushNotification.channelId,
                imageUrl = pushNotification.imageUrl,
                color = pushNotification.color,
                icon = pushNotification.icon,
                clickAction = pushNotification.clickAction
            )
        }
    }
}
