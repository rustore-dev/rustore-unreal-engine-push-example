// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"

#include "AndroidJavaClass.h"
#include "FURuStorePushClientConfig.h"
#include "FURuStoreError.h"
#include "FURuStoreFeatureAvailabilityResult.h"
#include "FURustoreTestNotificationPayload.h"
#include "RuStoreListener.h"
#include "URuStorePushClient.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCheckPushAvailabilityErrorDelegate, int64, requestId, FURuStoreError, error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCheckPushAvailabilityResponseDelegate, int64, requestId, FURuStoreFeatureAvailabilityResult, response);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGetTokenErrorDelegate, int64, requestId, FURuStoreError, error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGetTokenResponseDelegate, int64, requestId, FString, response);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDeleteTokenErrorDelegate, int64, requestId, FURuStoreError, error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDeleteTokenResponseDelegate, int64, requestId);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSendTestNotificationErrorDelegate, int64, requestId, FURuStoreError, error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSendTestNotificationResponseDelegate, int64, requestId);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSubscribeToTopicErrorDelegate, int64, requestId, FURuStoreError, error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSubscribeToTopicResponseDelegate, int64, requestId);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDesubscribeToTopicErrorDelegate, int64, requestId, FURuStoreError, error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDesubscribeToTopicResponseDelegate, int64, requestId);

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
    static const FString PluginVersion;

    UFUNCTION(BlueprintCallable, Category = "RuStore Push Client")
    bool GetIsInitialized();

    UFUNCTION(BlueprintCallable, Category = "RuStore Push Client")
    static URuStorePushClient* Instance();

	UFUNCTION(BlueprintCallable, Category = "RuStore Push Client")
    void SetAllowNativeErrorHandling(bool value);

    UFUNCTION(BlueprintCallable, Category = "RuStore Push Client")
    bool Init(FURuStorePushClientConfig config);
    
    UFUNCTION(BlueprintCallable, Category = "RuStore Push Client")
    void Dispose();

    void ConditionalBeginDestroy();

    long CheckPushAvailability(TFunction<void(long, TSharedPtr<FURuStoreFeatureAvailabilityResult, ESPMode::ThreadSafe>)> onSuccess, TFunction<void(long, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure);
    long GetToken(TFunction<void(long, FString)> onSuccess, TFunction<void(long, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure);
    long DeleteToken(TFunction<void(long)> onSuccess, TFunction<void(long, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure);
    long SendTestNotification(FURuStoreTestNotificationPayload& notification, TFunction<void(long)> onSuccess, TFunction<void(long, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure);
	long SubscribeToTopic(FString topicName, TFunction<void(long)> onSuccess, TFunction<void(long, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure);
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
    void SendTestNotification(FURuStoreTestNotificationPayload notification, int64& requestId);

    UPROPERTY(BlueprintAssignable, Category = "RuStore Push Client")
    FSendTestNotificationErrorDelegate OnSendTestNotificationError;

    UPROPERTY(BlueprintAssignable, Category = "RuStore Push Client")
    FSendTestNotificationResponseDelegate OnSendTestNotificationResponse;


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
