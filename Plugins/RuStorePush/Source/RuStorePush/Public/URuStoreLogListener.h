// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UObject/Interface.h"

#include "AndroidJavaObject.h"
#include "RuStoreListener.h"
#include "URuStoreLogListenerInterface.h"
#include "URuStoreLogListener.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FLogListenerOnLogDelegate, int64, requestId, FString, logString);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FLogListenerOnLogWarningDelegate, int64, requestId, FString, logString);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FLogListenerOnLogErrorDelegate, int64, requestId, FString, logString);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FLogListenerOnLogExceptionDelegate, int64, requestId, FURuStoreError, error);

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
    bool getIsInitialized();

    UFUNCTION(BlueprintCallable, Category = "RuStore LogListener")
    static URuStoreLogListener* Instance();

    UFUNCTION(BlueprintCallable, Category = "RuStore Log Listener")
    bool Init();

    UFUNCTION(BlueprintCallable, Category = "RuStore Log Listener")
    void Dispose();

    void ConditionalBeginDestroy();

    virtual void LogResponse_Implementation(int64 requestId, FString& logString) override;
    virtual void LogWarningResponse_Implementation(int64 requestId, FString& logString) override;
    virtual void LogErrorResponse_Implementation(int64 requestId, FString& logString) override;
    virtual void LogExceptionResponse_Implementation(int64 requestId, FURuStoreError& error) override;
    
    UPROPERTY(BlueprintAssignable, Category = "RuStore Log Listener")
    FLogListenerOnLogDelegate OnLog;

    UPROPERTY(BlueprintAssignable, Category = "RuStore Log Listener")
    FLogListenerOnLogWarningDelegate OnLogWarning;

    UPROPERTY(BlueprintAssignable, Category = "RuStore Log Listener")
    FLogListenerOnLogErrorDelegate OnLogError;

    UPROPERTY(BlueprintAssignable, Category = "RuStore Log Listener")
    FLogListenerOnLogExceptionDelegate OnLogException;

    AndroidJavaObject* GetJWrapper();
};
