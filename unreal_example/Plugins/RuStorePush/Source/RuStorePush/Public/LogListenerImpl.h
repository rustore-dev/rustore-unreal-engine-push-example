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
        TFunction<void(long, FString, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> _onLogVerbose;
        TFunction<void(long, FString, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> _onLogDebug;
        TFunction<void(long, FString, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> _onLogInfo;
        TFunction<void(long, FString, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> _onLogWarning;
        TFunction<void(long, FString, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> _onLogError;

    public:
        LogListenerImpl(
            TFunction<void(long, FString, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onLogVerbose,
            TFunction<void(long, FString, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onLogDebug,
            TFunction<void(long, FString, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onLogInfo,
            TFunction<void(long, FString, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onLogWarning,
            TFunction<void(long, FString, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onLogError
        ) : RuStoreListener("ru/rustore/unreal/pushclient/wrappers/LogListenerWrapper", "ru/rustore/unreal/pushclient/callbacks/UnrealLogListener")
        {
            _onLogVerbose = onLogVerbose;
            _onLogDebug = onLogDebug;
            _onLogInfo = onLogInfo;
            _onLogWarning = onLogWarning;
            _onLogError = onLogError;
        }
        
        virtual ~LogListenerImpl() { }

        void OnLogVerbose(FString message, AndroidJavaObject* errorObject);
        void OnLogDebug(FString message, AndroidJavaObject* errorObject);
        void OnLogInfo(FString message, AndroidJavaObject* errorObject);
        void OnLogWarning(FString message, AndroidJavaObject* errorObject);
        void OnLogError(FString message, AndroidJavaObject* errorObject);
    };
}
