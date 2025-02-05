// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "AndroidJavaObject.h"
#include "RuStoreListener.h"
#include "URuStoreLogListenerInterface.generated.h"

using namespace RuStoreSDK;

/*!
@brief Класс-адаптер для использования интерфейса IRuStoreLogListenerInterface в Blueprints.
*/
UINTERFACE(Blueprintable)
class RUSTOREPUSH_API URuStoreLogListenerInterface : public UInterface
{
    GENERATED_BODY()
};

/*!
@brief
    Интерфейс для получения и обработки событий SDK push-уведомлений.
    Обеспечивает методы для логирования различных уровней сообщений.
*/
class RUSTOREPUSH_API IRuStoreLogListenerInterface
{
    GENERATED_BODY()

public:
    /*!
    @brief
        Логирует подробное сообщение.
        Используется для записи детализированных логов, которые полезны для отладки.
    @param requestId Уникальный идентификатор запроса в рамках одного запуска приложения.
    @param message Текст сообщения для логирования.
    @param error Информация об ошибке.
    */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RuStore Log Listener Interface")
    void LogVerboseResponse(int64 requestId, FString& message, FURuStoreError& error);

    /*!
    @brief
        Логирует отладочное сообщение.
        Используется для записи логов, которые помогают в процессе отладки приложения.
    @param requestId Уникальный идентификатор запроса в рамках одного запуска приложения.
    @param message Текст сообщения для логирования.
    @param error Информация об ошибке.
    */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RuStore Log Listener Interface")
    void LogDebugResponse(int64 requestId, FString& message, FURuStoreError& error);

    /*!
    @brief
        Логирует информационное сообщение.
        Используется для записи стандартных логов, которые помогают отслеживать нормальное выполнение программы.
    @param requestId Уникальный идентификатор запроса в рамках одного запуска приложения.
    @param message Текст сообщения для логирования.
    @param error Информация об ошибке.
    */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RuStore Log Listener Interface")
    void LogInfoResponse(int64 requestId, FString& message, FURuStoreError& error);

    /*!
    @brief
        Логирует предупреждающее сообщение.
        Используется для записи логов, которые сигнализируют о потенциальных проблемах,
        которые не мешают выполнению программы, но могут потребовать внимания.
    @param requestId Уникальный идентификатор запроса в рамках одного запуска приложения.
    @param message Текст предупреждающего сообщения для логирования.
    @param error Информация об ошибке.
    */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RuStore Log Listener Interface")
    void LogWarnResponse(int64 requestId, FString& message, FURuStoreError& error);

    /*!
    @brief
        Логирует сообщение об ошибке.
        Используется для записи логов, которые сигнализируют о возникновении ошибок,
        требующих вмешательства или исправления.
    @param requestId Уникальный идентификатор запроса в рамках одного запуска приложения.
    @param message Текст сообщения об ошибке для логирования.
    @param error Информация об ошибке.
    */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RuStore Log Listener Interface")
    void LogErrorResponse(int64 requestId, FString& message, FURuStoreError& error);
};
