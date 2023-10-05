// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ErrorConverter.h"
#include "FURuStoreRemoteMessage.h"
#include "RuStoreListener.h"

namespace RuStoreSDK
{
    class RUSTOREPUSH_API MessagingServiceListenerImpl : public RuStoreListener
    {
    private:
        TFunction<void(long, FString)> _onNewToken;
        TFunction<void(long, TSharedPtr<FURuStoreRemoteMessage, ESPMode::ThreadSafe>)> _onMessageReceived;
        TFunction<void(long)> _onDeletedMessages;
        TFunction<void(long, TSharedPtr<TArray<FURuStoreError>, ESPMode::ThreadSafe>)> _onError;

    public:
        MessagingServiceListenerImpl(
            TFunction<void(long, FString)> onNewToken,
            TFunction<void(long, TSharedPtr<FURuStoreRemoteMessage, ESPMode::ThreadSafe>)> onMessageReceived,
            TFunction<void(long)> onDeletedMessages,
            TFunction<void(long, TSharedPtr<TArray<FURuStoreError>, ESPMode::ThreadSafe>)> onError
        ) : RuStoreListener("com/Plugins/RuStorePush/MessagingServiceListenerWrapper", "ru/rustore/unitysdk/pushclient/RuStoreUnityMessagingServiceListener")
        {
            _onNewToken = onNewToken;
            _onMessageReceived = onMessageReceived;
            _onDeletedMessages = onDeletedMessages;
            _onError = onError;
        }

        virtual ~MessagingServiceListenerImpl() { }

        void OnNewToken(FString token);
        void OnMessageReceived(AndroidJavaObject* responseObject);
        void OnDeletedMessages();
        void OnError(AndroidJavaObject* errorListObject);
    };
}
