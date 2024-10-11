// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EURuStoreClickActionType.generated.h"

UENUM(BlueprintType)
enum class EURuStoreClickActionType : uint8
{
    DEFAULT UMETA(DisplayName = "DEFAULT"),
    DEEP_LINK UMETA(DisplayName = "DEEP_LINK"),
    UNKNOWN UMETA(DisplayName = "UNKNOWN")
};
