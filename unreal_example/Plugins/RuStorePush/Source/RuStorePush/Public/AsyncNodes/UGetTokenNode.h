// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintAsyncActionBase.h"
#include "URuStorePushClient.h"
#include "UGetTokenNode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGetTokenPin, FString, response, FURuStoreError, error);

UCLASS()
class RUSTOREPUSH_API UGetTokenNode : public UBlueprintAsyncActionBase
{
    GENERATED_UCLASS_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FGetTokenPin Success;

    UPROPERTY(BlueprintAssignable)
    FGetTokenPin Failure;

    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "RuStore Push Client")
    static UGetTokenNode* GetTokenAsync(URuStorePushClient* target);
};
