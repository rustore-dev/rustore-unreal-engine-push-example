// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SimpleResponseListener.h"

namespace RuStoreSDK
{
    class RUSTOREPUSH_API SubscribeTopicListenerImpl : public SimpleResponseListener
    {
    public:
        SubscribeTopicListenerImpl(
            TFunction<void(long)> onSuccess,
            TFunction<void(long, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure,
            TFunction<void(RuStoreListener*)> onFinish
        ) : SimpleResponseListener("ru/rustore/unitysdk/pushclient/wrappers/SubscribeTopicListenerWrapper", "ru/rustore/unitysdk/pushclient/callbacks/SubscribeTopicListener", onSuccess, onFailure, onFinish)
        {
        }

        virtual ~SubscribeTopicListenerImpl();
    };
}
