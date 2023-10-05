// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "FURuStoreError.h"
#include "FURuStoreRemoteMessage.h"
#include "URuStoreMessagingServiceListenerInterface.generated.h"

UINTERFACE(Blueprintable)
class RUSTOREPUSH_API URuStoreMessagingServiceListenerInterface : public UInterface
{
    GENERATED_BODY()
};

class RUSTOREPUSH_API IRuStoreMessagingServiceListenerInterface
{
    GENERATED_BODY()
    
public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RuStore Messaging Service Listener Interface")
    void NewTokenResponse(int64 requestId, FString& token);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RuStore Messaging Service Listener Interface")
    void MessageReceivedResponse(int64 requestId, FURuStoreRemoteMessage& message);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RuStore Messaging Service Listener Interface")
    void DeletedMessagesResponse(int64 requestId);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RuStore Messaging Service Listener Interface")
    void ErrorResponse(int64 requestId, TArray<FURuStoreError>& errors);
};
