// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintAsyncActionBase.h"
#include "URuStorePushClient.h"
#include "USubscribeToTopicNode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSubscribeToTopicPin, FURuStoreError, error);

UCLASS()
class RUSTOREPUSH_API USubscribeToTopicNode : public UBlueprintAsyncActionBase
{
    GENERATED_UCLASS_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FSubscribeToTopicPin Success;

    UPROPERTY(BlueprintAssignable)
    FSubscribeToTopicPin Failure;

    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "RuStore Push Client")
    static USubscribeToTopicNode* SubscribeToTopicAsync(URuStorePushClient* target, FString topicName);
};
