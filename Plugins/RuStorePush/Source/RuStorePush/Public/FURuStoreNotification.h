// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FURuStoreNotification.generated.h"

USTRUCT(Blueprintable)
struct RUSTOREPUSH_API FURuStoreNotification
{
	GENERATED_USTRUCT_BODY()

public:
	FURuStoreNotification()
	{
		title = "";
		body = "";
		channelId = "";
		imageUrl = "";
		color = "";
		icon = "";
		clickAction = "";
	}

    UPROPERTY()
	FString title;

	UPROPERTY()
	FString body;

	UPROPERTY()
	FString channelId;

	UPROPERTY()
	FString imageUrl;

	UPROPERTY()
	FString color;

	UPROPERTY()
	FString icon;

	UPROPERTY()
	FString clickAction;
};
