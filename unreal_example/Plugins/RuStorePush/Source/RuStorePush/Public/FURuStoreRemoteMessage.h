// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FURuStoreNotification.h"
#include "FURuStoreRemoteMessage.generated.h"

/*!
@brief Параметры push-уведомления.
*/
USTRUCT(BlueprintType)
struct RUSTOREPUSH_API FURuStoreRemoteMessage
{
	GENERATED_USTRUCT_BODY()

public:
	/*!
	@brief Конструктор.
	*/
	FURuStoreRemoteMessage()
	{
		collapseKey = "";
		messageId = "";
		priority = 0;
		ttl = 0;
		from = "";
	}

	/*!
	@brief
		Уникальный ID сообщения.
		Является идентификатором каждого сообщения.
	*/
	UPROPERTY(BlueprintReadOnly)
	FString messageId;

	/*!
	@brief
		Возвращает значение приоритетности (на данный момент не учитывается).
		В настоящее время применяются варианты: 0 — UNKNOWN; 1 — HIGH; 2 — NORMAL.
	*/
	UPROPERTY(BlueprintReadOnly)
	int priority;

	/*!
	@brief Время жизни push-уведомления типа int в секундах.
	*/
	UPROPERTY(BlueprintReadOnly)
	int ttl;

	/*!
	@brief
		Поле, по которому можно понять, откуда пришло уведомление:
		для уведомлений, отправленных в топик, в поле отображается имя топика;
		в других случаях — часть вашего сервисного токена.
	*/
	UPROPERTY(BlueprintReadOnly)
	FString from;

	/*!
	@brief Идентификатор группы уведомлений (на данный момент не учитывается).
	*/
	UPROPERTY(BlueprintReadOnly)
	FString collapseKey;
	
	/*!
	@brief Словарь, в который можно передать дополнительные данные для уведомления.
	*/
	UPROPERTY(BlueprintReadOnly)
	TMap<FString, FString> data;
	
	/*!
	@brief Словарь data в виде массива байтов.
	*/
	UPROPERTY(BlueprintReadOnly)
	TArray<uint8> rawData;
	
	/*!
	@brief Объект уведомления.
	*/
	UPROPERTY(BlueprintReadOnly)
	FURuStoreNotification notification;
};
