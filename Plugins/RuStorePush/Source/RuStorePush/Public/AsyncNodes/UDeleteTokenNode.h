// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintAsyncActionBase.h"
#include "URuStorePushClient.h"
#include "UDeleteTokenNode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDeleteTokenPin, FURuStoreError, error);

UCLASS()
class RUSTOREPUSH_API UDeleteTokenNode : public UBlueprintAsyncActionBase
{
    GENERATED_UCLASS_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FDeleteTokenPin Success;

    UPROPERTY(BlueprintAssignable)
    FDeleteTokenPin Failure;

    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "RuStore Push Client")
    static UDeleteTokenNode* DeleteTokenAsync(URuStorePushClient* target);
};
