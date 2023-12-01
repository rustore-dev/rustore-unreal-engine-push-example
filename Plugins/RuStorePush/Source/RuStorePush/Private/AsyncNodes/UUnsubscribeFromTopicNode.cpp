// Copyright Epic Games, Inc. All Rights Reserved.

#include "UUnsubscribeFromTopicNode.h"

using namespace RuStoreSDK;

UUnsubscribeFromTopicNode::UUnsubscribeFromTopicNode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

UUnsubscribeFromTopicNode* UUnsubscribeFromTopicNode::UnsubscribeFromTopicAsync(URuStorePushClient* target, FString topicName)
{
    auto node = NewObject<UUnsubscribeFromTopicNode>(GetTransientPackage());
    
    target->UnsubscribeFromTopic(
        topicName,
        [target, node](long requestId) {
            node->Success.Broadcast(FURuStoreError());
        },
        [target, node](long requestId, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe> error) {
            node->Failure.Broadcast(*error);
        }
    );

    return node;
}
