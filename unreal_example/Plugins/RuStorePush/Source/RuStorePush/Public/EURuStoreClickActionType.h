// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EURuStoreClickActionType.generated.h"

/*!
@brief Тип поля clickAction в классе FURuStoreNotification.
*/
UENUM(BlueprintType)
enum class EURuStoreClickActionType : uint8
{
    /*!
    @brief По умолчанию.
    */
    DEFAULT UMETA(DisplayName = "DEFAULT"),
    
    /*!
    @brief Deeplink.
    */
    DEEP_LINK UMETA(DisplayName = "DEEP_LINK"),
    
    /*!
    @brief Значение не определено.
    */
    UNKNOWN UMETA(DisplayName = "UNKNOWN")
};
