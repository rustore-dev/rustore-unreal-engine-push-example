package ru.rustore.unitysdk.pushclient;

import java.util.List;

import ru.rustore.sdk.pushclient.messaging.exception.PushClientException;
import ru.rustore.sdk.pushclient.messaging.model.RemoteMessage;

public interface RuStoreUnityMessagingServiceListener {

    public void OnNewToken(String token);
    public void OnMessageReceived(RemoteMessage message);
    public void OnDeletedMessages();
    public void OnError(List<PushClientException> errors);
}
