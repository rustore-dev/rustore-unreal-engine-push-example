// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintAsyncActionBase.h"
#include "URuStorePushClient.h"
#include "UCheckPushAvailabilityNode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCheckPushAvailabilityPin, FURuStoreFeatureAvailabilityResult, response, FURuStoreError, error);

UCLASS()
class RUSTOREPUSH_API UCheckPushAvailabilityNode : public UBlueprintAsyncActionBase
{
    GENERATED_UCLASS_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FCheckPushAvailabilityPin Success;

    UPROPERTY(BlueprintAssignable)
    FCheckPushAvailabilityPin Failure;

    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "RuStore Push Client")
    static UCheckPushAvailabilityNode* CheckPushAvailabilityAsync(URuStorePushClient* target);
};
