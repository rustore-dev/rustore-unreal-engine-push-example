// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "ULaunchHandler.generated.h"

UCLASS(Blueprintable)
class RUSTOREPUSH_API ULaunchHandler : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Launch Handler")
    static bool GetLaunchIntentHasExtra();
};
