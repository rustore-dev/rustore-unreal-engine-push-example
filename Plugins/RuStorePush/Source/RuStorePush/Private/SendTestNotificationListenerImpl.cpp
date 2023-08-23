// Copyright Epic Games, Inc. All Rights Reserved.

#include "SendTestNotificationListenerImpl.h"

using namespace RuStoreSDK;

SendTestNotificationListenerImpl::~SendTestNotificationListenerImpl()
{
}

#if PLATFORM_ANDROID
extern "C"
{
    JNIEXPORT void JNICALL Java_com_Plugins_RuStorePush_SendTestNotificationListenerWrapper_NativeOnSuccess(JNIEnv* env, jobject, jlong pointer)
    {
        auto castobj = reinterpret_cast<SendTestNotificationListenerImpl*>(pointer);
        castobj->OnSuccess();
    }

    JNIEXPORT void JNICALL Java_com_Plugins_RuStorePush_SendTestNotificationListenerWrapper_NativeOnFailure(JNIEnv*, jobject, jlong pointer, jthrowable throwable)
    {
        auto obj = new AndroidJavaObject(throwable);
        obj->UpdateToGlobalRef();

        auto castobj = reinterpret_cast<SendTestNotificationListenerImpl*>(pointer);
        castobj->OnFailure(obj);
    }
}
#endif
