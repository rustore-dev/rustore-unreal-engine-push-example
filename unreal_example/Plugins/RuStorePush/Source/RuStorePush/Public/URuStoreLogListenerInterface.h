// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "AndroidJavaObject.h"
#include "RuStoreListener.h"
#include "URuStoreLogListenerInterface.generated.h"

using namespace RuStoreSDK;

UINTERFACE(Blueprintable)
class RUSTOREPUSH_API URuStoreLogListenerInterface : public UInterface
{
    GENERATED_BODY()
};

class RUSTOREPUSH_API IRuStoreLogListenerInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RuStore Log Listener Interface")
    void LogResponse(int64 requestId, FString& logString);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RuStore Log Listener Interface")
    void LogWarningResponse(int64 requestId, FString& logString);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RuStore Log Listener Interface")
    void LogErrorResponse(int64 requestId, FString& logString);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RuStore Log Listener Interface")
    void LogExceptionResponse(int64 requestId, FURuStoreError& error);
};
