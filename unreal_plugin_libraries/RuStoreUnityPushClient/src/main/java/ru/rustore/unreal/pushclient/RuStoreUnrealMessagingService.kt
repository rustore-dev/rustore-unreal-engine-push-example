package ru.rustore.unreal.pushclient

import ru.rustore.sdk.pushclient.messaging.exception.RuStorePushClientException
import ru.rustore.sdk.pushclient.messaging.model.RemoteMessage
import ru.rustore.sdk.pushclient.messaging.service.RuStoreMessagingService

class RuStoreUnrealMessagingService : RuStoreMessagingService() {

    override fun onNewToken(token: String) {
        RuStoreUnrealPushClient.onNewToken(token)
    }

    override fun onMessageReceived(message: RemoteMessage) {
        RuStoreUnrealPushClient.onMessageReceived(message)
    }

    override fun onDeletedMessages() {
        RuStoreUnrealPushClient.onDeletedMessages()
    }

    override fun onError(errors: List<RuStorePushClientException>) {
        RuStoreUnrealPushClient.onError(errors)
    }
}
