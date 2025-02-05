// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EURuStoreClickActionType.h"
#include "FURuStoreNotification.generated.h"

/*!
@brief Содержание push-уведомления.
*/
USTRUCT(Blueprintable)
struct RUSTOREPUSH_API FURuStoreNotification
{
	GENERATED_USTRUCT_BODY()

public:
	/*!
	@brief Конструктор.
	*/
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

	/*!
	@brief Заголовок уведомления.
	*/
    UPROPERTY(BlueprintReadOnly)
	FString title;

	/*!
	@brief Тело уведомления.
	*/
	UPROPERTY(BlueprintReadOnly)
	FString body;

	/*!
	@brief
		Возможность задать канал, в который отправится уведомление.
		Актуально для Android 8.0 и выше.
	*/
	UPROPERTY(BlueprintReadOnly)
	FString channelId;

	/*!
	@brief
		Прямая ссылка на изображение для вставки в уведомление.
		Изображение должно быть не более 1 Мбайт.
	*/
	UPROPERTY(BlueprintReadOnly)
	FString imageUrl;

	/*!
	@brief
		Цвет уведомления в HEX-формате, строкой.
		Например, #0077FF.
	*/
	UPROPERTY(BlueprintReadOnly)
	FString color;

	/*!
	@brief
		Значок уведомления из res/drawable в формате строки, которая совпадает с названием ресурса.
		Например, в res/drawable есть значок small_icon.xml, который доступен в коде через R.drawable.small_icon.
		Чтобы значок отображался в уведомлении, сервер должен указать в параметре icon значение small_icon.
	*/
	UPROPERTY(BlueprintReadOnly)
	FString icon;

	/*!
	@brief Intent action, с помощью которого будет открыта активити при клике на уведомление.
	*/
	UPROPERTY(BlueprintReadOnly)
	FString clickAction;

	/*!
	@brief Тип поля clickAction.
	*/
	UPROPERTY(BlueprintReadOnly)
	EURuStoreClickActionType clickActionType;
};
