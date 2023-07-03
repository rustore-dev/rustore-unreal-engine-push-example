// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SimpleResponseListenerT.h"

namespace RuStoreSDK
{
    class RUSTOREPUSH_API GetTokenListenerImpl : public SimpleResponseListenerT<FString>
    {
    public:
        GetTokenListenerImpl(
            TFunction<void(long, FString)> onSuccess,
            TFunction<void(long, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure,
            TFunction<void(RuStoreListener*)> onFinish
        ) : SimpleResponseListenerT<FString>("com/Plugins/RuStorePush/GetTokenListenerWrapper", "ru/rustore/unitysdk/pushclient/callbacks/GetTokenListener", onSuccess, onFailure, onFinish)
        {
        }

        virtual ~GetTokenListenerImpl() {}
    };
}
