// Copyright Epic Games, Inc. All Rights Reserved.

#include "UMyMessagingServiceListener.h"
#include "URuStoreCore.h"

UMyMessagingServiceListener* UMyMessagingServiceListener::InstanceImpl()
{
    return Super::Instance<UMyMessagingServiceListener>();
}

void UMyMessagingServiceListener::NewTokenResponse_Implementation(int64 requestId, FString& token)
{
    URuStoreCore::LogWarn("MessagingServiceListener", token);
}

void UMyMessagingServiceListener::MessageReceivedResponse_Implementation(int64 requestId, FURuStoreRemoteMessage& message)
{
    // to log
    URuStoreCore::LogWarn("MessagingServiceListener", message.messageId);

    // to blueprint event
    OnMessageReceivedResponse.Broadcast(requestId, message);
}

void UMyMessagingServiceListener::DeletedMessagesResponse_Implementation(int64 requestId)
{
    URuStoreCore::LogWarn("MessagingServiceListener", "Delete token");
}

void UMyMessagingServiceListener::ErrorResponse_Implementation(int64 requestId, TArray<FURuStoreError>& errors)
{
    URuStoreCore::LogWarn("MessagingServiceListener", "Error token");
}
