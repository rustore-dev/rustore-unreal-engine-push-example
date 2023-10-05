// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AndroidJavaObject.h"
#include "ErrorConverter.h"
#include "RuStoreListener.h"

namespace RuStoreSDK
{
    class RUSTOREPUSH_API LogListenerImpl : public RuStoreListener
    {
    private:
        TFunction<void(long, FString)> _onLog;
        TFunction<void(long, FString)> _onLogWarning;
        TFunction<void(long, FString)> _onLogError;
        TFunction<void(long, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> _onLogException;

    public:
        LogListenerImpl(
            TFunction<void(long, FString)> onLog,
            TFunction<void(long, FString)> onLogWarning,
            TFunction<void(long, FString)> onLogError,
            TFunction<void(long, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onLogException
        ) : RuStoreListener("com/Plugins/RuStorePush/LogListenerWrapper", "ru/rustore/unitysdk/pushclient/callbacks/UnityLogListener")
        {
            _onLog = onLog;
            _onLogWarning = onLogWarning;
            _onLogError = onLogError;
            _onLogException = onLogException;
        }
        
        virtual ~LogListenerImpl() { }

        void OnLog(FString logString);
        void OnLogWarning(FString logString);
        void OnLogError(FString logString);
        void OnLogException(AndroidJavaObject* errorObject);
    };
}
