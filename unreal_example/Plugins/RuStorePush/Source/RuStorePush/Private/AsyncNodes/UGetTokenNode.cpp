// Copyright Epic Games, Inc. All Rights Reserved.

#include "UGetTokenNode.h"

using namespace RuStoreSDK;

UGetTokenNode::UGetTokenNode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

UGetTokenNode* UGetTokenNode::GetTokenAsync(URuStorePushClient* target)
{
    auto node = NewObject<UGetTokenNode>(GetTransientPackage());
    
    target->GetToken(
        [target, node](long requestId, FString response) {
            node->Success.Broadcast(response, FURuStoreError());
        },
        [target, node](long requestId, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe> error) {
            node->Failure.Broadcast(FString(), *error);
        }
    );

    return node;
}
