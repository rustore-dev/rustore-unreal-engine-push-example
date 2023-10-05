// Copyright Epic Games, Inc. All Rights Reserved.

#include "MessagingServiceListenerImpl.h"
#include "CallbackHandler.h"
#include "URuStoreCore.h"

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
    response->messageId = responseObject->GetFString("messageId");
    response->priority = responseObject->GetInt("priority");
    response->ttl = responseObject->GetInt("ttl");
    response->collapseKey = responseObject->GetFString("collapseKey");

    auto jData = responseObject->GetAJObject("data", "Ljava/util/Map;");
    auto jDataSet = jData->CallSpecificAJObject("entrySet", "Ljava/util/Set;");
    auto jDataArray = jDataSet->CallSpecificAJObject("toArray", "[Ljava/lang/Object;");
    auto size = jDataSet->CallInt("size");

    for (int i = 0; i < size; i++)
    {
        auto p = jDataArray->GetAJObjectArrayElement(i);
        if (p != nullptr)
        {
            auto itemKey = p->CallFString("getKey");

            auto itemVal = p->CallFString("getValue");
            response->data.Add(itemKey, itemVal);

            delete p;
        }
    }
    delete jDataArray;
    delete jDataSet;
    delete jData;

    auto jRawData = responseObject->GetAJObject("rawData", "[B");
    if (jRawData != nullptr)
    {
        int byteArraySize = jRawData->CallInt("size");

        for (int i = 0; i < byteArraySize; i++)
        {
            uint8 item = jRawData->CallByte("get", i);
            response->rawData.Add(item);
        }
        delete jRawData;
    }

    URuStoreCore::LogWarn("rustore_debug", "Read notification");

    auto jNotification = responseObject->GetAJObject("notification", "Lru/rustore/sdk/pushclient/messaging/model/Notification;");
    if (jNotification != nullptr)
    {
        response->notification.title = jNotification->GetFString("title");
        response->notification.body = jNotification->GetFString("body");
        response->notification.channelId = jNotification->GetFString("channelId");
        response->notification.color = jNotification->GetFString("color");
        response->notification.icon = jNotification->GetFString("icon");
        response->notification.clickAction = jNotification->GetFString("clickAction");

        auto jImageUrl = jNotification->GetAJObject("imageUrl", "Landroid/net/Uri;");
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
