// Copyright Epic Games, Inc. All Rights Reserved.

#include "ErrorListener.h"

using namespace RuStoreSDK;

void ErrorListener::OnFailure(AndroidJavaObject* errorObject)
{
    auto error = TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>(ErrorConverter::Convert(errorObject));
    delete errorObject;

    auto listener = GetWeakPtr();
    CallbackHandler::AddCallback([this, listener, error]() {
        if (listener.IsValid())
        {
            this->_onFailure(this->GetId(), error);
            this->_onFinish(this);
        }
    });
}
