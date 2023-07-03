// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FURuStoreNotification.h"
#include "FURuStoreRemoteMessage.generated.h"

USTRUCT(BlueprintType)
struct RUSTOREPUSH_API FURuStoreRemoteMessage
{
	GENERATED_USTRUCT_BODY()

public:
	FURuStoreRemoteMessage()
	{
		collapseKey = "";
		messageId = "";
		priority = 0;
		ttl = 0;
	}

	UPROPERTY(BlueprintReadOnly)
	FString messageId;

	UPROPERTY(BlueprintReadOnly)
	int priority;

	UPROPERTY(BlueprintReadOnly)
	int ttl;

	UPROPERTY(BlueprintReadOnly)
	FString collapseKey;
	
	UPROPERTY(BlueprintReadOnly)
	TMap<FString, FString> data;
	
	UPROPERTY(BlueprintReadOnly)
	TArray<uint8> rawData;
	
	UPROPERTY(BlueprintReadOnly)
	FURuStoreNotification notification;
};
