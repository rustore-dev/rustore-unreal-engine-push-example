// Copyright Epic Games, Inc. All Rights Reserved.

#include "UCheckPushAvailabilityNode.h"

using namespace RuStoreSDK;

UCheckPushAvailabilityNode::UCheckPushAvailabilityNode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

UCheckPushAvailabilityNode* UCheckPushAvailabilityNode::CheckPushAvailabilityAsync(URuStorePushClient* target)
{
    auto node = NewObject<UCheckPushAvailabilityNode>(GetTransientPackage());
 
    target->CheckPushAvailability(
        [target, node](long requestId, TSharedPtr<FURuStoreFeatureAvailabilityResult, ESPMode::ThreadSafe> response) {
            node->Success.Broadcast(*response, FURuStoreError());
        },
        [target, node](long requestId, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe> error) {
            node->Failure.Broadcast(FURuStoreFeatureAvailabilityResult(), *error);
        }
    );

    return node;
}
