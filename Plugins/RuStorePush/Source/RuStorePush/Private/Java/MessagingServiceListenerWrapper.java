// Copyright Epic Games, Inc. All Rights Reserved.

package com.Plugins.RuStorePush;

import com.Plugins.RuStoreCore.IRuStoreListener;
import java.util.List;
import ru.rustore.sdk.pushclient.messaging.exception.RuStorePushClientException;
import ru.rustore.sdk.pushclient.messaging.model.RemoteMessage;
import ru.rustore.unitysdk.pushclient.model.PushConverter;
import ru.rustore.unitysdk.pushclient.model.PushMessage;
import ru.rustore.unitysdk.pushclient.RuStoreUnityMessagingServiceListener;

public class MessagingServiceListenerWrapper implements IRuStoreListener, RuStoreUnityMessagingServiceListener
{
    private static MessagingServiceListenerWrapper instance = null;

    private Object mutex = new Object();
    private long cppPointer = 0;

    private native void NativeOnNewToken(long pointer, String token);
    private native void NativeOnMessageReceived(long pointer, PushMessage message);
    private native void NativeOnDeletedMessages(long pointer);
    private native void NativeOnError(long pointer, List<RuStorePushClientException> errors);

    public static synchronized MessagingServiceListenerWrapper GetInstance() {
        return instance;
    }

    public MessagingServiceListenerWrapper(long cppPointer) {
        this.cppPointer = cppPointer;
        instance = this;
    }

    @Override
    public void OnNewToken(String token) {
        synchronized (mutex) {
            if (cppPointer != 0) {
                NativeOnNewToken(cppPointer, token);
            }
        }
    }

    @Override
    public void OnMessageReceived(RemoteMessage message) {
        synchronized (mutex) {
            if (cppPointer != 0) {
                PushMessage pushMessage = PushConverter.Convert(message);
                NativeOnMessageReceived(cppPointer, pushMessage);
            }
        }
    }

    @Override
    public void OnDeletedMessages() {
        synchronized (mutex) {
            if (cppPointer != 0) {
                NativeOnDeletedMessages(cppPointer);
            }
        }
    }

    @Override
    public void OnError(List<RuStorePushClientException> errors) {
        synchronized (mutex) {
            if (cppPointer != 0) {
                NativeOnError(cppPointer, errors);
            }
        }
    }

    public void DisposeCppPointer() {
        synchronized (mutex) {
            cppPointer = 0;
        }
    }
}
