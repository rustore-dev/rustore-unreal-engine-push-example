// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EURuStoreClickActionType.h"
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
		clickActionType = EURuStoreClickActionType::UNKNOWN;
	}

    UPROPERTY(BlueprintReadOnly)
	FString title;

	UPROPERTY(BlueprintReadOnly)
	FString body;

	UPROPERTY(BlueprintReadOnly)
	FString channelId;

	UPROPERTY(BlueprintReadOnly)
	FString imageUrl;

	UPROPERTY(BlueprintReadOnly)
	FString color;

	UPROPERTY(BlueprintReadOnly)
	FString icon;

	UPROPERTY(BlueprintReadOnly)
	FString clickAction;

	UPROPERTY(BlueprintReadOnly)
	EURuStoreClickActionType clickActionType;
};
