// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SimpleResponseListener.h"

namespace RuStoreSDK
{
    class RUSTOREPUSH_API DeleteTokenListenerImpl : public SimpleResponseListener
    {
    public:
        DeleteTokenListenerImpl(
            TFunction<void(long)> onSuccess,
            TFunction<void(long, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure,
            TFunction<void(RuStoreListener*)> onFinish
        ) : SimpleResponseListener("com/Plugins/RuStorePush/DeleteTokenListenerWrapper", "ru/rustore/unitysdk/pushclient/callbacks/DeleteTokenListener", onSuccess, onFailure, onFinish)
        {
        }

        virtual ~DeleteTokenListenerImpl() {}
    };
}
