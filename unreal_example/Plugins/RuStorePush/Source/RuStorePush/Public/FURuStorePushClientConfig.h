// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EURuStoreClientIdType.h"
#include "URuStoreMessagingServiceListenerInterface.h"
#include "URuStoreLogListenerInterface.h"
#include "FURuStorePushClientConfig.generated.h"

/*!
@brief Параметры инициализации push-клиента.
*/
USTRUCT(BlueprintType)
struct RUSTOREPUSH_API FURuStorePushClientConfig
{
	GENERATED_USTRUCT_BODY()

public:
	/*!
	@brief Конструктор.
	*/
	FURuStorePushClientConfig()
	{
		bAllowNativeErrorHandling = false;
		messagingServiceListener = TScriptInterface<URuStoreMessagingServiceListenerInterface>();
		logListener = TScriptInterface<URuStoreLogListenerInterface>();
	}

	/*!
	@brief
		Обработка ошибок в нативном SDK.
		true — разрешает обработку ошибок, false — запрещает.
	*/
	UPROPERTY(BlueprintReadWrite)
	bool bAllowNativeErrorHandling;

	/*!
	@brief Объект, реализующий интерфейс для получения и обработки данных push-уведомлений.
	*/
	UPROPERTY(BlueprintReadWrite)
	TScriptInterface<URuStoreMessagingServiceListenerInterface> messagingServiceListener;

	/*!
	@brief Объект, реализующий интерфейс для получения и обработки событий SDK push-уведомлений.
	*/
	UPROPERTY(BlueprintReadWrite)
	TScriptInterface<URuStoreLogListenerInterface> logListener;
};
