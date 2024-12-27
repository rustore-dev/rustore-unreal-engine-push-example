// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FURuStoreError.h"
#include "FURuStoreFeatureAvailabilityResult.generated.h"

/*!
@brief Проверка доступности функционала.
*/
USTRUCT(BlueprintType)
struct RUSTORECORE_API FURuStoreFeatureAvailabilityResult
{
	GENERATED_USTRUCT_BODY()

	/*!
	@brief Конструктор.
	*/
	FURuStoreFeatureAvailabilityResult()
	{
		isAvailable = false;
	}

	/*!
	@brief
		Информация о доступности.
		Если все условия выполняются, возвращается FURuStoreFeatureAvailabilityResult::isAvailable == true.
		В противном случае возвращается FURuStoreFeatureAvailabilityResult::isAvailable == false.
	*/
	UPROPERTY(BlueprintReadWrite)
	bool isAvailable;

	/*!
	@brief Информация об ошибке.
	*/
	UPROPERTY(BlueprintReadWrite)
	FURuStoreError cause;
};
