package ru.rustore.unitysdk.pushclient

import ru.rustore.sdk.pushclient.messaging.exception.RuStorePushClientException
import ru.rustore.sdk.pushclient.messaging.model.RemoteMessage
import ru.rustore.sdk.pushclient.messaging.service.RuStoreMessagingService

class RuStoreUnityMessagingService : RuStoreMessagingService() {

    override fun onNewToken(token: String) {
        RuStoreUnityPushClient.onNewToken(token)
    }

    override fun onMessageReceived(message: RemoteMessage) {
        RuStoreUnityPushClient.onMessageReceived(message)
    }

    override fun onDeletedMessages() {
        RuStoreUnityPushClient.onDeletedMessages()
    }

    override fun onError(errors: List<RuStorePushClientException>) {
        RuStoreUnityPushClient.onError(errors)
    }
}
