// Copyright Epic Games, Inc. All Rights Reserved.

#include "USubscribeToTopicNode.h"

using namespace RuStoreSDK;

USubscribeToTopicNode::USubscribeToTopicNode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

USubscribeToTopicNode* USubscribeToTopicNode::SubscribeToTopicAsync(URuStorePushClient* target, FString topicName)
{
    auto node = NewObject<USubscribeToTopicNode>(GetTransientPackage());
    
    target->SubscribeToTopic(
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
