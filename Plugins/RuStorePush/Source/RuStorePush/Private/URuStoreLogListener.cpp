// Copyright Epic Games, Inc. All Rights Reserved.

#include "URuStoreLogListener.h"
#include "LogListenerImpl.h"
#include "URuStoreCore.h"

URuStoreLogListener* URuStoreLogListener::_instance = nullptr;
bool URuStoreLogListener::_bIsInstanceInitialized = false;

bool URuStoreLogListener::getIsInitialized()
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
        [this](long requestId, FString logString) {
            LogResponse_Implementation(requestId, logString);
        },
        [this](long requestId, FString logString) {
            LogWarningResponse_Implementation(requestId, logString);
        },
        [this](long requestId, FString logString) {
            LogErrorResponse_Implementation(requestId, logString);
        },
        [this](long requestId, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe> error) {
            LogExceptionResponse_Implementation(requestId, *error);
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

void URuStoreLogListener::LogResponse_Implementation(int64 requestId, FString& logString)
{
    OnLog.Broadcast(requestId, logString);
}

void URuStoreLogListener::LogWarningResponse_Implementation(int64 requestId, FString& logString)
{
    OnLogWarning.Broadcast(requestId, logString);
}

void URuStoreLogListener::LogErrorResponse_Implementation(int64 requestId, FString& logString)
{
    OnLogError.Broadcast(requestId, logString);
}

void URuStoreLogListener::LogExceptionResponse_Implementation(int64 requestId, FURuStoreError& error)
{
    OnLogException.Broadcast(requestId, error);
}

AndroidJavaObject* URuStoreLogListener::GetJWrapper()
{
    return listener.IsValid() ? listener->GetJWrapper() : nullptr;
}
