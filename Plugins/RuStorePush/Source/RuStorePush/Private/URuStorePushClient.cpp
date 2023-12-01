// Copyright Epic Games, Inc. All Rights Reserved.

#include "URuStorePushClient.h"
#include "FeatureAvailabilityListenerImpl.h"
#include "GetTokenListenerImpl.h"
#include "DeleteTokenListenerImpl.h"
#include "SendTestNotificationListenerImpl.h"
#include "SubscribeTopicListenerImpl.h"
#include "URuStoreCore.h"
#include "URuStoreLogListener.h"
#include "URuStoreMessagingServiceListener.h"

using namespace RuStoreSDK;

const FString URuStorePushClient::PluginVersion = "1.0";
URuStorePushClient* URuStorePushClient::_instance = nullptr;
bool URuStorePushClient::_bIsInstanceInitialized = false;

bool URuStorePushClient::GetIsInitialized()
{
    return bIsInitialized;
}

URuStorePushClient* URuStorePushClient::Instance()
{
    if (!_bIsInstanceInitialized)
    {
        _bIsInstanceInitialized = true;
        _instance = NewObject<URuStorePushClient>(GetTransientPackage());
    }

    return _instance;
}

void URuStorePushClient::SetAllowNativeErrorHandling(bool value)
{
    if (!URuStoreCore::IsPlatformSupported()) return;
    if (bIsInitialized) return;

    _bAllowNativeErrorHandling = value;
    _clientWrapper->CallVoid("setErrorHandling", value);
}

bool URuStorePushClient::Init(FURuStorePushClientConfig config)
{
    if (!URuStoreCore::IsPlatformSupported()) return false;
    if (bIsInitialized) return false;

    _instance->AddToRoot();

    URuStoreCore::Instance()->Init();

    _application = new JavaApplication();

    auto clientJavaClass = MakeShared<AndroidJavaClass>("ru/rustore/unitysdk/pushclient/RuStoreUnityPushClient");
    clientJavaClass->CallStaticVoid("init", _application, config.projectId, FString("unreal"));
    _clientWrapper = clientJavaClass->GetStaticAJObject("INSTANCE");

    AndroidJavaObject jMessagingServiceListenerNULL("ru/rustore/unitysdk/pushclient/RuStoreUnityMessagingServiceListener", 0, false);
    AndroidJavaObject jLogListenerNULL("ru/rustore/unitysdk/pushclient/callbacks/UnityLogListener", 0, false);

    auto messagingServiceListener = (config.messagingServiceListener != nullptr)
        ? Cast<URuStoreMessagingServiceListener>(config.messagingServiceListener.GetObject())
        : nullptr;

    auto logListener = (config.logListener != nullptr)
        ? Cast<URuStoreLogListener>(config.logListener.GetObject())
        : nullptr;

    AndroidJavaObject* jMessagingServiceListener = (messagingServiceListener != nullptr)
        ? messagingServiceListener->GetJWrapper()
        : &jMessagingServiceListenerNULL;

    AndroidJavaObject* jLogListener = (logListener != nullptr)
        ? logListener->GetJWrapper()
        : &jLogListenerNULL;

    _clientWrapper->CallVoid("init", config.bAllowNativeErrorHandling, jMessagingServiceListener, jLogListener);
	
    return bIsInitialized = true;
}

void URuStorePushClient::Dispose()
{
    if (bIsInitialized)
    {
        bIsInitialized = false;
        ListenerRemoveAll();
        delete _clientWrapper;
        delete _application;
        _instance->RemoveFromRoot();
    }
}

void URuStorePushClient::ConditionalBeginDestroy()
{
    Super::ConditionalBeginDestroy();

    Dispose();
    if (_bIsInstanceInitialized) _bIsInstanceInitialized = false;
}

long URuStorePushClient::CheckPushAvailability(TFunction<void(long, TSharedPtr<FURuStoreFeatureAvailabilityResult, ESPMode::ThreadSafe>)> onSuccess, TFunction<void(long, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure)
{
    if (!URuStoreCore::IsPlatformSupported(onFailure)) return 0;
    if (!bIsInitialized) return 0;

    auto listener = ListenerBind(new FeatureAvailabilityListenerImpl(onSuccess, onFailure, [this](RuStoreListener* item) { ListenerUnbind(item); }));
    _clientWrapper->CallVoid("checkPushAvailability", listener->GetJWrapper());

    return listener->GetId();
}

long URuStorePushClient::GetToken(TFunction<void(long, FString)> onSuccess, TFunction<void(long, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure)
{
    if (!URuStoreCore::IsPlatformSupported(onFailure)) return 0;
    if (!bIsInitialized) return 0;

    auto listener = ListenerBind(new GetTokenListenerImpl(onSuccess, onFailure, [this](RuStoreListener* item) { ListenerUnbind(item); }));
    _clientWrapper->CallVoid("getToken", listener->GetJWrapper());

    return listener->GetId();
}

long URuStorePushClient::DeleteToken(TFunction<void(long)> onSuccess, TFunction<void(long, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure)
{
    if (!URuStoreCore::IsPlatformSupported(onFailure)) return 0;
    if (!bIsInitialized) return 0;

    auto listener = ListenerBind(new DeleteTokenListenerImpl(onSuccess, onFailure, [this](RuStoreListener* item) { ListenerUnbind(item); }));
    _clientWrapper->CallVoid("deleteToken", listener->GetJWrapper());

    return listener->GetId();
}

long URuStorePushClient::SubscribeToTopic(FString topicName, TFunction<void(long)> onSuccess, TFunction<void(long, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure)
{
    if (!URuStoreCore::IsPlatformSupported(onFailure)) return 0;
    if (!bIsInitialized) return 0;

    auto listener = ListenerBind(new SubscribeTopicListenerImpl(onSuccess, onFailure, [this](RuStoreListener* item) { ListenerUnbind(item); }));
    _clientWrapper->CallVoid("subscribeToTopic", topicName, listener->GetJWrapper());

    return listener->GetId();
}

long URuStorePushClient::UnsubscribeFromTopic(FString topicName, TFunction<void(long)> onSuccess, TFunction<void(long, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure)
{
    if (!URuStoreCore::IsPlatformSupported(onFailure)) return 0;
    if (!bIsInitialized) return 0;

    auto listener = ListenerBind(new SubscribeTopicListenerImpl(onSuccess, onFailure, [this](RuStoreListener* item) { ListenerUnbind(item); }));
    _clientWrapper->CallVoid("unsubscribeFromTopic", topicName, listener->GetJWrapper());

    return listener->GetId();
}

void URuStorePushClient::CheckPushAvailability(int64& requestId)
{
    requestId = CheckPushAvailability(
        [this](long requestId, TSharedPtr<FURuStoreFeatureAvailabilityResult, ESPMode::ThreadSafe> response) {
            OnCheckPushAvailabilityResponse.Broadcast(requestId, *response);
        },
        [this](long requestId, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe> error) {
            OnCheckPushAvailabilityError.Broadcast(requestId, *error);
        }
    );
}

void URuStorePushClient::GetToken(int64& requestId)
{
    requestId = GetToken(
        [this](long requestId, FString response) {
            OnGetTokenResponse.Broadcast(requestId, response);
        },
        [this](long requestId, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe> error) {
            OnGetTokenError.Broadcast(requestId, *error);
        }
    );
}

void URuStorePushClient::DeleteToken(int64& requestId)
{
    requestId = DeleteToken(
        [this](long requestId) {
            OnDeleteTokenResponse.Broadcast(requestId);
        },
        [this](long requestId, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe> error) {
            OnDeleteTokenError.Broadcast(requestId, *error);
        }
    );
}

void URuStorePushClient::SubscribeToTopic(FString topicName, int64& requestId)
{
	requestId = SubscribeToTopic(
		topicName,
		[this](long requestId) {
            OnSubscribeToTopicResponse.Broadcast(requestId);
		},
		[this](long requestId, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe> error) {
            OnSubscribeToTopicError.Broadcast(requestId, *error);
		}
	);
}

void URuStorePushClient::UnsubscribeFromTopic(FString topicName, int64& requestId)
{
	requestId = UnsubscribeFromTopic(
		topicName,
		[this](long requestId) {
            OnUnsubscribeFromTopicResponse.Broadcast(requestId);
		},
		[this](long requestId, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe> error) {
            OnUnsubscribeFromTopicError.Broadcast(requestId, *error);
		}
	);
}
