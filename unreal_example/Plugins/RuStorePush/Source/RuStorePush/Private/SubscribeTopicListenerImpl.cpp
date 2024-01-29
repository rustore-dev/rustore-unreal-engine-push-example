// Copyright Epic Games, Inc. All Rights Reserved.

#include "SubscribeTopicListenerImpl.h"

using namespace RuStoreSDK;

SubscribeTopicListenerImpl::~SubscribeTopicListenerImpl()
{
}

#if PLATFORM_ANDROID
extern "C"
{
    JNIEXPORT void JNICALL Java_ru_rustore_unitysdk_pushclient_wrappers_SubscribeTopicListenerWrapper_NativeOnSuccess(JNIEnv* env, jobject, jlong pointer)
    {
        auto castobj = reinterpret_cast<SubscribeTopicListenerImpl*>(pointer);
        castobj->OnSuccess();
    }

    JNIEXPORT void JNICALL Java_ru_rustore_unitysdk_pushclient_wrappers_SubscribeTopicListenerWrapper_NativeOnFailure(JNIEnv*, jobject, jlong pointer, jthrowable throwable)
    {
        auto obj = new AndroidJavaObject(throwable);
        obj->UpdateToGlobalRef();

        auto castobj = reinterpret_cast<SubscribeTopicListenerImpl*>(pointer);
        castobj->OnFailure(obj);
    }
}
#endif
