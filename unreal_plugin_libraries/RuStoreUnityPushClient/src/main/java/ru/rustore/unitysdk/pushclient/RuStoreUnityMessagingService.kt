package ru.rustore.unitysdk.pushclient

import ru.rustore.sdk.pushclient.messaging.exception.PushClientException
import ru.rustore.sdk.pushclient.messaging.model.RemoteMessage
import ru.rustore.sdk.pushclient.messaging.service.RuStoreMessagingService
import ru.rustore.unreal.pushclient.RuStoreUnrealPushClient

class RuStoreUnityMessagingService : RuStoreMessagingService() {

    override fun onNewToken(token: String) {
        RuStoreUnrealPushClient.onNewToken(token)
    }

    override fun onMessageReceived(message: RemoteMessage) {
        RuStoreUnrealPushClient.onMessageReceived(message)
    }

    override fun onDeletedMessages() {
        RuStoreUnrealPushClient.onDeletedMessages()
    }

    override fun onError(errors: List<PushClientException>) {
        RuStoreUnrealPushClient.onError(errors)
    }
}
