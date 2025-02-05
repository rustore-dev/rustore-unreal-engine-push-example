// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"

#include "AndroidJavaClass.h"
#include "FURuStorePushClientConfig.h"
#include "FURuStoreError.h"
#include "FURuStoreFeatureAvailabilityResult.h"
#include "FURustoreTestNotificationPayload.h"
#include "JavaApplication.h"
#include "RuStoreListener.h"
#include "URuStorePushClient.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCheckPushAvailabilityErrorDelegate, int64, requestId, FURuStoreError, error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCheckPushAvailabilityResponseDelegate, int64, requestId, FURuStoreFeatureAvailabilityResult, response);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGetTokenErrorDelegate, int64, requestId, FURuStoreError, error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGetTokenResponseDelegate, int64, requestId, FString, response);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDeleteTokenErrorDelegate, int64, requestId, FURuStoreError, error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDeleteTokenResponseDelegate, int64, requestId);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSubscribeToTopicErrorDelegate, int64, requestId, FURuStoreError, error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSubscribeToTopicResponseDelegate, int64, requestId);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDesubscribeToTopicErrorDelegate, int64, requestId, FURuStoreError, error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDesubscribeToTopicResponseDelegate, int64, requestId);

/*!
@brief Класс реализует API для приёма push-сообщений через сервисы RuStore.
*/
UCLASS(Blueprintable)
class RUSTOREPUSH_API URuStorePushClient : public UObject, public RuStoreListenerContainer
{
	GENERATED_BODY()

private:
    static URuStorePushClient* _instance;
    static bool _bIsInstanceInitialized;

    bool bIsInitialized = false;
    bool _bAllowNativeErrorHandling = false;
    AndroidJavaObject* _clientWrapper = nullptr;
    JavaApplication* _application = nullptr;

public:
    /*!
    @brief Версия плагина.
    */
    static const FString PluginVersion;

    /*!
    @brief Проверка инициализации push-клиента.
    @return Возвращает true, если синглтон инициализирован, в противном случае — false.
    */
    UFUNCTION(BlueprintCallable, Category = "RuStore Push Client")
    bool GetIsInitialized();

    /*!
    @brief
        Получить экземпляр URuStorePushClient.
    @return
        Возвращает указатель на единственный экземпляр URuStorePushClient (реализация паттерна Singleton).
        Если экземпляр еще не создан, создает его.
    */
    UFUNCTION(BlueprintCallable, Category = "RuStore Push Client")
    static URuStorePushClient* Instance();

    /*!
    @brief Обработка ошибок в нативном SDK.
    @param value true — разрешает обработку ошибок, false — запрещает.
    */
	UFUNCTION(BlueprintCallable, Category = "RuStore Push Client")
    void SetAllowNativeErrorHandling(bool value);

    /*!
    @brief Выполняет инициализацию синглтона URuStorePushClient.
    @param config
        Объект класса FURuStorePushClientConfig.
        Содержит параметры инициализации платежного клиента.
    @return Возвращает true, если инициализация была успешно выполнена, в противном случае — false.
    */
    UFUNCTION(BlueprintCallable, Category = "RuStore Push Client")
    bool Init(FURuStorePushClientConfig config);
    
    /*!
    @brief Деинициализация синглтона, если дальнейшая работа с объектом больше не планируется.
    */
    UFUNCTION(BlueprintCallable, Category = "RuStore Push Client")
    void Dispose();

    void ConditionalBeginDestroy();

    /*!
    @brief
        Проверка доступности приёма push-сообщений.
        Если все условия выполняются, возвращается FURuStoreFeatureAvailabilityResult::isAvailable == true.
        В противном случае возвращается FURuStoreFeatureAvailabilityResult::isAvailable == false.
    @param onSuccess
        Действие, выполняемое при успешном завершении операции.
        Возвращает requestId типа long и объект FURuStoreFeatureAvailabilityResult с информацией о доступности приёма push-сообщений.
    @param onFailure
        Действие, выполняемое в случае ошибки.
        Возвращает requestId типа long и объект типа FURuStoreError с информацией об ошибке.
    @return Возвращает уникальный в рамках одного запуска приложения requestId.
    */
    long CheckPushAvailability(TFunction<void(long, TSharedPtr<FURuStoreFeatureAvailabilityResult, ESPMode::ThreadSafe>)> onSuccess, TFunction<void(long, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure);
    
    /*!
    @brief Получить текущий push-токен пользователя.
    @param onSuccess
        Действие, выполняемое при успешном завершении операции.
        Возвращает requestId типа long и push-токен в виде строки.
    @param onFailure
        Действие, выполняемое в случае ошибки.
        Возвращает requestId типа long и объект типа FURuStoreError с информацией об ошибке.
    @return Возвращает уникальный в рамках одного запуска приложения requestId.
    */
    long GetToken(TFunction<void(long, FString)> onSuccess, TFunction<void(long, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure);
    
    /*!
    @brief Удалить текущий push-токен пользователя.
    @param onSuccess
        Действие, выполняемое при успешном завершении операции.
        Возвращает requestId типа long.
    @param onFailure
        Действие, выполняемое в случае ошибки.
        Возвращает requestId типа long и объект типа FURuStoreError с информацией об ошибке.
    @return Возвращает уникальный в рамках одного запуска приложения requestId.
    */
    long DeleteToken(TFunction<void(long)> onSuccess, TFunction<void(long, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure);
	
    /*!
    @brief Подписка на push-уведомления по топику.
    @param topicName Название топика.
    @param onSuccess
        Действие, выполняемое при успешном завершении операции.
        Возвращает requestId типа long.
    @param onFailure
        Действие, выполняемое в случае ошибки.
        Возвращает requestId типа long и объект типа FURuStoreError с информацией об ошибке.
    @return Возвращает уникальный в рамках одного запуска приложения requestId.
    */
    long SubscribeToTopic(FString topicName, TFunction<void(long)> onSuccess, TFunction<void(long, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure);
	
    /*!
    @brief Отписка от топика.
    @param topicName Название топика.
    @param onSuccess
        Действие, выполняемое при успешном завершении операции.
        Возвращает requestId типа long.
    @param onFailure
        Действие, выполняемое в случае ошибки.
        Возвращает requestId типа long и объект типа FURuStoreError с информацией об ошибке.
    @return Возвращает уникальный в рамках одного запуска приложения requestId.
    */
    long UnsubscribeFromTopic(FString topicName, TFunction<void(long)> onSuccess, TFunction<void(long, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure);

    // 
    UFUNCTION(BlueprintCallable, Category = "RuStore Push Client")
    void CheckPushAvailability(int64& requestId);

    UPROPERTY(BlueprintAssignable, Category = "RuStore Push Client")
    FCheckPushAvailabilityErrorDelegate OnCheckPushAvailabilityError;

    UPROPERTY(BlueprintAssignable, Category = "RuStore Push Client")
    FCheckPushAvailabilityResponseDelegate OnCheckPushAvailabilityResponse;


    // 
    UFUNCTION(BlueprintCallable, Category = "RuStore Push Client")
    void GetToken(int64& requestId);

    UPROPERTY(BlueprintAssignable, Category = "RuStore Push Client")
    FGetTokenErrorDelegate OnGetTokenError;

    UPROPERTY(BlueprintAssignable, Category = "RuStore Push Client")
    FGetTokenResponseDelegate OnGetTokenResponse;


    // 
    UFUNCTION(BlueprintCallable, Category = "RuStore Push Client")
    void DeleteToken(int64& requestId);

    UPROPERTY(BlueprintAssignable, Category = "RuStore Push Client")
    FDeleteTokenErrorDelegate OnDeleteTokenError;

    UPROPERTY(BlueprintAssignable, Category = "RuStore Push Client")
    FDeleteTokenResponseDelegate OnDeleteTokenResponse;


	// 
	UFUNCTION(BlueprintCallable, Category = "RuStore Push Client")
	void SubscribeToTopic(FString topicName, int64& requestId);

	UPROPERTY(BlueprintAssignable, Category = "RuStore Push Client")
	FSubscribeToTopicErrorDelegate OnSubscribeToTopicError;

	UPROPERTY(BlueprintAssignable, Category = "RuStore Push Client")
	FSubscribeToTopicResponseDelegate OnSubscribeToTopicResponse;


	// 
	UFUNCTION(BlueprintCallable, Category = "RuStore Push Client")
	void UnsubscribeFromTopic(FString topicName, int64& requestId);

	UPROPERTY(BlueprintAssignable, Category = "RuStore Push Client")
	FDesubscribeToTopicErrorDelegate OnUnsubscribeFromTopicError;

	UPROPERTY(BlueprintAssignable, Category = "RuStore Push Client")
	FDesubscribeToTopicResponseDelegate OnUnsubscribeFromTopicResponse;
};
