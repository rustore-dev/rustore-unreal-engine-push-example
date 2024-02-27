// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UObject/Interface.h"

#include "AndroidJavaObject.h"
#include "RuStoreListener.h"
#include "URuStoreMessagingServiceListenerInterface.h"
#include "URuStoreMessagingServiceListener.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FMessagingServiceNewTokenDelegate, int64, requestId, FString, logString);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FMessagingServiceMessageReceivedDelegate, int64, requestId, FURuStoreRemoteMessage, message);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMessagingServiceDeletedMessagesDelegate, int64, requestId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FMessagingServiceErrorDelegate, int64, requestId, TArray<FURuStoreError>, errors);

using namespace RuStoreSDK;

UCLASS(Blueprintable)
class RUSTOREPUSH_API URuStoreMessagingServiceListener : public UObject, public IRuStoreMessagingServiceListenerInterface, public RuStoreListenerContainer
{
	GENERATED_BODY()

private:
    static URuStoreMessagingServiceListener* _instance;
    static bool _bIsInstanceInitialized;

    bool bIsInitialized = false;
    bool _bAllowNativeErrorHandling;
    TSharedPtr<RuStoreListener, ESPMode::ThreadSafe> listener;

public:
    UFUNCTION(BlueprintCallable, Category = "RuStore Messaging Service Listener")
    bool GetIsInitialized();

    UFUNCTION(BlueprintCallable, Category = "RuStore Messaging Service Listener")
    static URuStoreMessagingServiceListener* Instance();

    template<typename T>
    static T* Instance()
    {
        if (!_bIsInstanceInitialized)
        {
            _bIsInstanceInitialized = true;
            auto instanceT = NewObject<T>(GetTransientPackage());
            auto instanceCast = Cast<URuStoreMessagingServiceListener>(instanceT);
            _instance = instanceCast;
        }

        return Cast<T>(_instance);
    }

    UFUNCTION(BlueprintCallable, Category = "RuStore Messaging Service Listener")
    bool Init();

    UFUNCTION(BlueprintCallable, Category = "RuStore Messaging Service Listener")
    void Dispose();

    void ConditionalBeginDestroy();

    virtual void NewTokenResponse_Implementation(int64 requestId, FString& token) override;
    virtual void MessageReceivedResponse_Implementation(int64 requestId, FURuStoreRemoteMessage& message) override;
    virtual void DeletedMessagesResponse_Implementation(int64 requestId) override;
    virtual void ErrorResponse_Implementation(int64 requestId, TArray<FURuStoreError>& errors) override;

    UPROPERTY(BlueprintAssignable, Category = "RuStore Messaging Service Listener")
    FMessagingServiceNewTokenDelegate OnNewTokenResponse;

    UPROPERTY(BlueprintAssignable, Category = "RuStore Messaging Service Listener")
    FMessagingServiceMessageReceivedDelegate OnMessageReceivedResponse;

    UPROPERTY(BlueprintAssignable, Category = "RuStore Messaging Service Listener")
    FMessagingServiceDeletedMessagesDelegate OnDeletedMessagesResponse;

    UPROPERTY(BlueprintAssignable, Category = "RuStore Messaging Service Listener")
    FMessagingServiceErrorDelegate OnErrorResponse;

    AndroidJavaObject* GetJWrapper();
};
