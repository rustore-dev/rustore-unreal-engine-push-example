// Copyright Epic Games, Inc. All Rights Reserved.

#include "UMyMessagingServiceListener.h"
#include "URuStoreCore.h"

UMyMessagingServiceListener* UMyMessagingServiceListener::InstanceImpl()
{
    return Super::Instance<UMyMessagingServiceListener>();
}

void UMyMessagingServiceListener::NewTokenResponse_Implementation(int64 requestId, FString& token)
{
    URuStoreCore::ShowToast(token);
}

void UMyMessagingServiceListener::MessageReceivedResponse_Implementation(int64 requestId, FURuStoreRemoteMessage& message)
{
    URuStoreCore::ShowToast(message.messageId);
}

void UMyMessagingServiceListener::DeletedMessagesResponse_Implementation(int64 requestId)
{
    URuStoreCore::ShowToast("Delete token");
}

void UMyMessagingServiceListener::ErrorResponse_Implementation(int64 requestId, TArray<FURuStoreError>& errors)
{
    URuStoreCore::ShowToast("Error token");
}
