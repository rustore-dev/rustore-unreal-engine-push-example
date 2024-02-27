// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EURuStoreClientIdType.generated.h"

UENUM(BlueprintType)
enum class EURuStoreClientIdType : uint8
{
    GAID UMETA(DisplayName = "GAID"),
    OAID UMETA(DisplayName = "OAID"),
    NONE UMETA(DisplayName = "NONE")
};
