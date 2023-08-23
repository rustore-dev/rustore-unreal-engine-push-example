// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FURuStoreTestNotificationPayload.generated.h"

USTRUCT(Blueprintable)
struct RUSTOREPUSH_API FURuStoreTestNotificationPayload
{
	GENERATED_USTRUCT_BODY()

public:
	FURuStoreTestNotificationPayload()
	{
		title = "";
		body = "";
		imageUrl = "";
	}

    UPROPERTY(BlueprintReadWrite)
	FString title;

	UPROPERTY(BlueprintReadWrite)
	FString body;

	UPROPERTY(BlueprintReadWrite)
	FString imageUrl;

	UPROPERTY(BlueprintReadWrite)
	TMap<FString, FString> data;
};
