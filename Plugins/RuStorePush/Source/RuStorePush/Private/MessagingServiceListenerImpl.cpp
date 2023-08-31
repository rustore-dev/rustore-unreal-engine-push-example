// Copyright Epic Games, Inc. All Rights Reserved.

#include "MessagingServiceListenerImpl.h"
#include "AndroidJavaClass.h"
#include "CallbackHandler.h"

using namespace RuStoreSDK;

void MessagingServiceListenerImpl::OnNewToken(FString token)
{
    auto listener = GetWeakPtr();
    CallbackHandler::AddCallback([this, listener, token]() {
        if (listener.IsValid())
        {
            this->_onNewToken(this->GetId(), token);
        }
    });
}

void MessagingServiceListenerImpl::OnMessageReceived(AndroidJavaObject* responseObject)
{
    auto response = MakeShared<FURuStoreRemoteMessage, ESPMode::ThreadSafe>();

    response->messageId = responseObject->CallFString("getMessageId");
    response->priority = responseObject->CallInt("getPriority");
    response->ttl = responseObject->CallInt("getTtl");
    response->collapseKey = responseObject->CallFString("getCollapseKey");

    auto jData = responseObject->CallSpecificAJObject("getData", "Ljava/util/Map;");
	jData->SetInterfaceName("java/util/Map");

    auto jKeySet = jData->CallSpecificAJObject("keySet", "Ljava/util/Set;");
    auto jKeyArray = jKeySet->CallSpecificAJObject("toArray", "[Ljava/lang/Object;");
    auto size = jKeySet->CallInt("size");

    for (int i = 0; i < size; i++)
    {
		FString itemKey = jKeyArray->GetFStringArrayElement(i);
		AndroidJavaClass* converter = new AndroidJavaClass("com/Plugins/RuStorePush/MessagingServiceListenerWrapper");
		FString itemVal = converter->CallStaticFString("GetValue", jData, itemKey);
		response->data.Add(itemKey, itemVal);

		delete converter;
    }
    delete jKeyArray;
    delete jKeySet;
    delete jData;

	auto jRawData = responseObject->CallByteArray("getRawData");
    if (jRawData != nullptr)
    {
		response->rawData.Append(jRawData->GetData(), jRawData->Num());

        delete jRawData;
    }

    auto jNotification = responseObject->CallSpecificAJObject("getNotification", "Lru/rustore/sdk/pushclient/messaging/model/Notification;");
    if (jNotification != nullptr)
    {
        response->notification.title = jNotification->CallFString("getTitle");
        response->notification.body = jNotification->CallFString("getBody");
        response->notification.channelId = jNotification->CallFString("getChannelId");
        response->notification.color = jNotification->CallFString("getColor");
        response->notification.icon = jNotification->CallFString("getIcon");
        response->notification.clickAction = jNotification->CallFString("getClickAction");

        AndroidJavaObject* jImageUrl = jNotification->CallSpecificAJObject("getImageUrl", "Landroid/net/Uri;");
        if (jImageUrl != nullptr)
        {
            response->notification.imageUrl = jImageUrl->CallFString("toString");

            delete jImageUrl;
        }

        delete jNotification;
    }

    delete responseObject;

    auto listener = GetWeakPtr();
    CallbackHandler::AddCallback([this, listener, response]() {
        if (listener.IsValid())
        {
            this->_onMessageReceived(this->GetId(), response);
        }
    });
}

void MessagingServiceListenerImpl::OnDeletedMessages()
{
    auto listener = GetWeakPtr();
    CallbackHandler::AddCallback([this, listener]() {
        if (listener.IsValid())
        {
            this->_onDeletedMessages(this->GetId());
        }
    });
}

void MessagingServiceListenerImpl::OnError(AndroidJavaObject* errorListObject)
{
    auto errorTArray = MakeShared<TArray<FURuStoreError>, ESPMode::ThreadSafe>();
    auto size = errorListObject->CallInt("size");
    for (int i = 0; i < size; i++)
    {
        auto p = errorListObject->CallAJObject("get", i);
        if (p != nullptr)
        {
            auto item = ErrorConverter::Convert(p);
            errorTArray->Add(*item);

            delete p;
        }
    }
    delete errorListObject;

    auto listener = GetWeakPtr();
    CallbackHandler::AddCallback([this, listener, errorTArray]() {
        if (listener.IsValid())
        {
            this->_onError(this->GetId(), errorTArray);
        }
    });
}

#if PLATFORM_ANDROID
extern "C"
{
    JNIEXPORT void JNICALL Java_com_Plugins_RuStorePush_MessagingServiceListenerWrapper_NativeOnNewToken(JNIEnv* env, jobject, jlong pointer, jstring result)
    {
        auto castobj = reinterpret_cast<MessagingServiceListenerImpl*>(pointer);
        castobj->OnNewToken(JavaTypeConverter::Convert(env, result));
    }

    JNIEXPORT void JNICALL Java_com_Plugins_RuStorePush_MessagingServiceListenerWrapper_NativeOnMessageReceived(JNIEnv*, jobject, jlong pointer, jobject result)
    {
        auto obj = new AndroidJavaObject(result);
        obj->UpdateToGlobalRef();

        auto castobj = reinterpret_cast<MessagingServiceListenerImpl*>(pointer);
        castobj->OnMessageReceived(obj);
    }

    JNIEXPORT void JNICALL Java_com_Plugins_RuStorePush_MessagingServiceListenerWrapper_NativeOnDeletedMessages(JNIEnv*, jobject, jlong pointer)
    {
        auto castobj = reinterpret_cast<MessagingServiceListenerImpl*>(pointer);
        castobj->OnDeletedMessages();
    }

    JNIEXPORT void JNICALL Java_com_Plugins_RuStorePush_MessagingServiceListenerWrapper_NativeOnError(JNIEnv*, jobject, jlong pointer, jobject errors)
    {
        auto obj = new AndroidJavaObject(errors);
        obj->UpdateToGlobalRef();

        auto castobj = reinterpret_cast<MessagingServiceListenerImpl*>(pointer);
        castobj->OnError(obj);
    }
}
#endif
