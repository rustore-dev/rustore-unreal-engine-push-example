// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "FURuStoreError.h"
#include "FURuStoreRemoteMessage.h"
#include "URuStoreMessagingServiceListenerInterface.generated.h"

/*!
@brief Класс-адаптер для использования интерфейса IRuStoreMessagingServiceListenerInterface в Blueprints.
*/
UINTERFACE(Blueprintable)
class RUSTOREPUSH_API URuStoreMessagingServiceListenerInterface : public UInterface
{
    GENERATED_BODY()
};

/*!
@brief Интерфейс для получения и обработки данных push-уведомлений.
*/
class RUSTOREPUSH_API IRuStoreMessagingServiceListenerInterface
{
    GENERATED_BODY()
    
public:
    /*!
    @brief
        Метод вызывается при получении нового push-токена.
        После вызова этого метода приложение становится ответственно за передачу нового push-токена на свой сервер.
    @param requestId Уникальный идентификатор запроса в рамках одного запуска приложения.
    @param token Значение нового токена.
    */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RuStore Messaging Service Listener Interface")
    void NewTokenResponse(int64 requestId, FString& token);

    /*!
    @brief
        Метод вызывается при получении нового push-уведомления.
        Если в объекте notification есть данные, SDK самостоятельно отображает уведомление.
        Если вы не хотите этого, используйте объект data, а notification оставьте пустым.
        Метод вызывается в любом случае.
    @param requestId Уникальный идентификатор запроса в рамках одного запуска приложения.
    @param message Информация о push-уведомлении.
    */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RuStore Messaging Service Listener Interface")
    void MessageReceivedResponse(int64 requestId, FURuStoreRemoteMessage& message);

    /*!
    @brief
        Метод вызывается, если одно или несколько push-уведомлений не доставлены на устройство.
        Например, если время жизни уведомления истекло до момента доставки.
        При вызове этого метода рекомендуется синхронизироваться со своим сервером, чтобы не пропустить данные.
    @param requestId Уникальный идентификатор запроса в рамках одного запуска приложения.
    */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RuStore Messaging Service Listener Interface")
    void DeletedMessagesResponse(int64 requestId);

    /*!
    @brief Метод вызывается, если в момент инициализации возникает ошибка.
    @param requestId Уникальный идентификатор запроса в рамках одного запуска приложения.
    @param errors Список объектов с ошибками.
    */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RuStore Messaging Service Listener Interface")
    void ErrorResponse(int64 requestId, TArray<FURuStoreError>& errors);
};
