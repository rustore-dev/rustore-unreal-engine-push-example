// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "URuStoreMessagingServiceListenerInterface.h"
#include "URuStoreLogListenerInterface.h"
#include "FURuStorePushClientConfig.generated.h"

USTRUCT(BlueprintType)
struct RUSTOREPUSH_API FURuStorePushClientConfig
{
	GENERATED_USTRUCT_BODY()

public:
	FURuStorePushClientConfig()
	{
		bAllowNativeErrorHandling = false;

		messagingServiceListener = TScriptInterface<URuStoreMessagingServiceListenerInterface>();
		logListener = TScriptInterface<URuStoreLogListenerInterface>();
		projectId = "";
		bTestModeEnable = false;
	}

	UPROPERTY(BlueprintReadWrite)
	bool bAllowNativeErrorHandling;

	UPROPERTY(BlueprintReadWrite)
	TScriptInterface<URuStoreMessagingServiceListenerInterface> messagingServiceListener;

	UPROPERTY(BlueprintReadWrite)
	TScriptInterface<URuStoreLogListenerInterface> logListener;

	UPROPERTY(BlueprintReadWrite)
	FString projectId;

	UPROPERTY(BlueprintReadWrite)
	bool bTestModeEnable;
};
