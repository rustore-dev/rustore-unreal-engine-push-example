// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UObject/Interface.h"

#include "AndroidJavaObject.h"
#include "FURuStoreError.h"
#include "RuStoreListener.h"
#include "URuStoreLogListenerInterface.h"
#include "URuStoreLogListener.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FLogListenerOnLogVerboseDelegate, int64, requestId, FString, message, FURuStoreError, error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FLogListenerOnLogDebugDelegate, int64, requestId, FString, message, FURuStoreError, error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FLogListenerOnLogInfoDelegate, int64, requestId, FString, message, FURuStoreError, error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FLogListenerOnLogWarningDelegate, int64, requestId, FString, message, FURuStoreError, error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FLogListenerOnLogErrorDelegate, int64, requestId, FString, message, FURuStoreError, error);

using namespace RuStoreSDK;

UCLASS(Blueprintable)
class RUSTOREPUSH_API URuStoreLogListener : public UObject, public IRuStoreLogListenerInterface, public RuStoreListenerContainer
{
    GENERATED_BODY()

private:
    static URuStoreLogListener* _instance;
    static bool _bIsInstanceInitialized;

    bool bIsInitialized = false;
    bool _bAllowNativeErrorHandling;
    TSharedPtr<RuStoreListener, ESPMode::ThreadSafe> listener;

public:
    template<typename T>
    static T* Instance()
    {
        if (!_bIsInstanceInitialized)
        {
            _bIsInstanceInitialized = true;
            auto instanceT = NewObject<T>(GetTransientPackage());
            auto instanceCast = Cast<URuStoreLogListener>(instanceT);
            _instance = instanceCast;
        }

        return Cast<T>(_instance);
    }

    UFUNCTION(BlueprintCallable, Category = "RuStore Log Listener")
    bool GetIsInitialized();

    UFUNCTION(BlueprintCallable, Category = "RuStore LogListener")
    static URuStoreLogListener* Instance();

    UFUNCTION(BlueprintCallable, Category = "RuStore Log Listener")
    bool Init();

    UFUNCTION(BlueprintCallable, Category = "RuStore Log Listener")
    void Dispose();

    void ConditionalBeginDestroy();

    virtual void LogVerboseResponse_Implementation(int64 requestId, FString& message, FURuStoreError& error);
    virtual void LogDebugResponse_Implementation(int64 requestId, FString& message, FURuStoreError& error);
    virtual void LogInfoResponse_Implementation(int64 requestId, FString& message, FURuStoreError& error);
    virtual void LogWarningResponse_Implementation(int64 requestId, FString& message, FURuStoreError& error);
    virtual void LogErrorResponse_Implementation(int64 requestId, FString& message, FURuStoreError& error);

    UPROPERTY(BlueprintAssignable, Category = "RuStore Log Listener")
    FLogListenerOnLogVerboseDelegate OnLogVerbose;

    UPROPERTY(BlueprintAssignable, Category = "RuStore Log Listener")
    FLogListenerOnLogDebugDelegate OnLogDebug;

    UPROPERTY(BlueprintAssignable, Category = "RuStore Log Listener")
    FLogListenerOnLogInfoDelegate OnLogInfo;

    UPROPERTY(BlueprintAssignable, Category = "RuStore Log Listener")
    FLogListenerOnLogWarningDelegate OnLogWarning;

    UPROPERTY(BlueprintAssignable, Category = "RuStore Log Listener")
    FLogListenerOnLogErrorDelegate OnLogError;

    AndroidJavaObject* GetJWrapper();
};
