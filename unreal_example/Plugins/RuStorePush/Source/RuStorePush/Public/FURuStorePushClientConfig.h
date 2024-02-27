// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EURuStoreClientIdType.h"
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
	}

	UPROPERTY(BlueprintReadWrite)
	bool bAllowNativeErrorHandling;

	UPROPERTY(BlueprintReadWrite)
	TScriptInterface<URuStoreMessagingServiceListenerInterface> messagingServiceListener;

	UPROPERTY(BlueprintReadWrite)
	TScriptInterface<URuStoreLogListenerInterface> logListener;
};
