// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "URuStoreMessagingServiceListener.h"
#include "UMyMessagingServiceListener.generated.h"

UCLASS(Blueprintable)
class RUSTOREPUSHAPP_API UMyMessagingServiceListener : public URuStoreMessagingServiceListener
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "My Messaging Service Listener")
    static UMyMessagingServiceListener* InstanceImpl();

    virtual void NewTokenResponse_Implementation(int64 requestId, FString& token) override;
    virtual void MessageReceivedResponse_Implementation(int64 requestId, FURuStoreRemoteMessage& message) override;
    virtual void DeletedMessagesResponse_Implementation(int64 requestId) override;
    virtual void ErrorResponse_Implementation(int64 requestId, TArray<FURuStoreError>& errors) override;
};
