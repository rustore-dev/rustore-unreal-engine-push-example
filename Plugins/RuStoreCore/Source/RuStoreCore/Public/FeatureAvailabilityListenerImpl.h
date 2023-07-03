// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "URuStoreCore.h"
#include "FUFeatureAvailabilityResult.h"
#include "ResponseListener.h"

namespace RuStoreSDK
{
	class RUSTORECORE_API FeatureAvailabilityListenerImpl : public ResponseListener<FUFeatureAvailabilityResult>
	{
	protected:
		FUFeatureAvailabilityResult* ConvertResponse(AndroidJavaObject* responseObject) override;

	public:
		FeatureAvailabilityListenerImpl(
			TFunction<void(long requestId, TSharedPtr<FUFeatureAvailabilityResult, ESPMode::ThreadSafe>)> onSuccess,
			TFunction<void(long requestId, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure,
			TFunction<void(RuStoreListener*)> onFinish
		) : ResponseListener<FUFeatureAvailabilityResult>("com/Plugins/RuStoreCore/FeatureAvailabilityListenerWrapper", "ru/rustore/unitysdk/core/callbacks/FeatureAvailabilityListener", onSuccess, onFailure, onFinish)
		{
		}

		virtual ~FeatureAvailabilityListenerImpl();
	};
}
