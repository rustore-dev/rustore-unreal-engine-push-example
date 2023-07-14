// Copyright Epic Games, Inc. All Rights Reserved.

#include "URuStoreMessagingServiceListener.h"
#include "MessagingServiceListenerImpl.h"
#include "URuStoreCore.h"

URuStoreMessagingServiceListener* URuStoreMessagingServiceListener::_instance = nullptr;
bool URuStoreMessagingServiceListener::_bIsInstanceInitialized = false;

bool URuStoreMessagingServiceListener::GetIsInitialized()
{
    return bIsInitialized;
}

URuStoreMessagingServiceListener* URuStoreMessagingServiceListener::Instance()
{
    if (!_bIsInstanceInitialized)
    {
        _bIsInstanceInitialized = true;
        _instance = NewObject<URuStoreMessagingServiceListener>(GetTransientPackage());
    }

    return _instance;
}

bool URuStoreMessagingServiceListener::Init()
{
    if (!URuStoreCore::IsPlatformSupported()) return false;
    if (bIsInitialized) return false;

    _instance->AddToRoot();

    listener = ListenerBind(new MessagingServiceListenerImpl(
        [this](long requestId, FString token) {
            NewTokenResponse_Implementation(requestId, token);
        },
        [this](long requestId, TSharedPtr<FURuStoreRemoteMessage, ESPMode::ThreadSafe> message) {
            MessageReceivedResponse_Implementation(requestId, *message);
        },
        [this](long requestId) {
            DeletedMessagesResponse_Implementation(requestId);
        },
        [this](long requestId, TSharedPtr<TArray<FURuStoreError>, ESPMode::ThreadSafe> errors) {
            ErrorResponse_Implementation(requestId, *errors);
        }
    ));

    return true;
}

void URuStoreMessagingServiceListener::Dispose()
{
    if (bIsInitialized)
    {
        bIsInitialized = false;
        ListenerRemoveAll();
        _instance->RemoveFromRoot();
    }
}

void URuStoreMessagingServiceListener::ConditionalBeginDestroy()
{
    Super::ConditionalBeginDestroy();

    Dispose();
    if (_bIsInstanceInitialized) _bIsInstanceInitialized = false;
}

void URuStoreMessagingServiceListener::NewTokenResponse_Implementation(int64 requestId, FString& token)
{
    OnNewTokenResponse.Broadcast(requestId, token);
}

void URuStoreMessagingServiceListener::MessageReceivedResponse_Implementation(int64 requestId, FURuStoreRemoteMessage& message)
{
    OnMessageReceivedResponse.Broadcast(requestId, message);
}

void URuStoreMessagingServiceListener::DeletedMessagesResponse_Implementation(int64 requestId)
{
    OnDeletedMessagesResponse.Broadcast(requestId);
}

void URuStoreMessagingServiceListener::ErrorResponse_Implementation(int64 requestId, TArray<FURuStoreError>& errors)
{
    OnErrorResponse.Broadcast(requestId, errors);
}

AndroidJavaObject* URuStoreMessagingServiceListener::GetJWrapper()
{
    return listener.IsValid() ? listener->GetJWrapper() : nullptr;
}
