// Copyright Epic Games, Inc. All Rights Reserved.

#include "UDeleteTokenNode.h"

using namespace RuStoreSDK;

UDeleteTokenNode::UDeleteTokenNode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

UDeleteTokenNode* UDeleteTokenNode::DeleteTokenAsync(URuStorePushClient* target)
{
    auto node = NewObject<UDeleteTokenNode>(GetTransientPackage());
    
    target->DeleteToken(
        [target, node](long requestId) {
            node->Success.Broadcast(FURuStoreError());
        },
        [target, node](long requestId, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe> error) {
            node->Failure.Broadcast(*error);
        }
    );

    return node;
}
