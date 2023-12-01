// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintAsyncActionBase.h"
#include "URuStorePushClient.h"
#include "UUnsubscribeFromTopicNode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUnsubscribeFromTopicPin, FURuStoreError, error);

UCLASS()
class RUSTOREPUSH_API UUnsubscribeFromTopicNode : public UBlueprintAsyncActionBase
{
    GENERATED_UCLASS_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FUnsubscribeFromTopicPin Success;

    UPROPERTY(BlueprintAssignable)
    FUnsubscribeFromTopicPin Failure;

    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "RuStore Push Client")
    static UUnsubscribeFromTopicNode* UnsubscribeFromTopicAsync(URuStorePushClient* target, FString topicName);
};
