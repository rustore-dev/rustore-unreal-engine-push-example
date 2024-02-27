// Copyright Epic Games, Inc. All Rights Reserved.

#include "URuStoreLogListener.h"
#include "LogListenerImpl.h"
#include "URuStoreCore.h"

URuStoreLogListener* URuStoreLogListener::_instance = nullptr;
bool URuStoreLogListener::_bIsInstanceInitialized = false;

bool URuStoreLogListener::GetIsInitialized()
{
    return bIsInitialized;
}

URuStoreLogListener* URuStoreLogListener::Instance()
{
    if (!_bIsInstanceInitialized)
    {
        _bIsInstanceInitialized = true;
        _instance = NewObject<URuStoreLogListener>(GetTransientPackage());
    }

    return _instance;
}

bool URuStoreLogListener::Init()
{
    if (!URuStoreCore::IsPlatformSupported()) return false;
    if (bIsInitialized) return false;

    _instance->AddToRoot();

    listener = ListenerBind(new LogListenerImpl(
        [this](long requestId, FString message, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe> error) {
            LogVerboseResponse_Implementation(requestId, message, *error);
        },
        [this](long requestId, FString message, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe> error) {
            LogDebugResponse_Implementation(requestId, message, *error);
        },
        [this](long requestId, FString message, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe> error) {
            LogInfoResponse_Implementation(requestId, message, *error);
        },
        [this](long requestId, FString message, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe> error) {
            LogWarningResponse_Implementation(requestId, message, *error);
        },
        [this](long requestId, FString message, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe> error) {
            LogErrorResponse_Implementation(requestId, message, *error);
        }
    ));

    return true;
}

void URuStoreLogListener::Dispose()
{
    if (bIsInitialized)
    {
        bIsInitialized = false;
        ListenerRemoveAll();
        _instance->RemoveFromRoot();
    }
}

void URuStoreLogListener::ConditionalBeginDestroy()
{
    Super::ConditionalBeginDestroy();

    Dispose();
    if (_bIsInstanceInitialized) _bIsInstanceInitialized = false;
}

void URuStoreLogListener::LogVerboseResponse_Implementation(int64 requestId, FString& message, FURuStoreError& error)
{
    OnLogVerbose.Broadcast(requestId, message, error);
}

void URuStoreLogListener::LogDebugResponse_Implementation(int64 requestId, FString& message, FURuStoreError& error)
{
    OnLogDebug.Broadcast(requestId, message, error);
}

void URuStoreLogListener::LogInfoResponse_Implementation(int64 requestId, FString& message, FURuStoreError& error)
{
    OnLogInfo.Broadcast(requestId, message, error);
}

void URuStoreLogListener::LogWarningResponse_Implementation(int64 requestId, FString& message, FURuStoreError& error)
{
    OnLogWarning.Broadcast(requestId, message, error);
}

void URuStoreLogListener::LogErrorResponse_Implementation(int64 requestId, FString& message, FURuStoreError& error)
{
    OnLogError.Broadcast(requestId, message, error);
}

AndroidJavaObject* URuStoreLogListener::GetJWrapper()
{
    return listener.IsValid() ? listener->GetJWrapper() : nullptr;
}
