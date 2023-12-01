// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SimpleResponseListener.h"

namespace RuStoreSDK
{
    class RUSTOREPUSH_API SendTestNotificationListenerImpl : public SimpleResponseListener
    {
    public:
        SendTestNotificationListenerImpl(
            TFunction<void(long)> onSuccess,
            TFunction<void(long, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure,
            TFunction<void(RuStoreListener*)> onFinish
        ) : SimpleResponseListener("ru/rustore/unitysdk/pushclient/wrappers/SendTestNotificationListenerWrapper", "ru/rustore/unitysdk/pushclient/callbacks/SendTestNotificationListener", onSuccess, onFailure, onFinish)
        {
        }

        virtual ~SendTestNotificationListenerImpl();
    };
}
