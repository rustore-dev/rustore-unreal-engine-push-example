// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ErrorListener.h"

namespace RuStoreSDK
{
    template <typename T>
    class SimpleResponseListenerT : public ErrorListener
    {
    private:
        TFunction<void(long, T)> _onSuccess;

    protected:
        SimpleResponseListenerT(
            FString className,
            FString interfaceName,
            TFunction<void(long, T)> onSuccess,
            TFunction<void(long, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure,
            TFunction<void(RuStoreListener*)> onFinish
        ) : ErrorListener(className, interfaceName, onFailure, onFinish)
        {
            _onSuccess = onSuccess;
        }

        virtual ~SimpleResponseListenerT() { }

    public:
        void OnSuccess(T response)
        {
            auto listener = GetWeakPtr();
            CallbackHandler::AddCallback([this, listener, response]() {
                if (listener.IsValid())
                {
                    this->_onSuccess(this->GetId(), response);
                    this->_onFinish(this);
                }
            });
        }
    };
}
