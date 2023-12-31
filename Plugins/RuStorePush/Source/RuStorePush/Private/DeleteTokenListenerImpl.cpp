// Copyright Epic Games, Inc. All Rights Reserved.

#include "DeleteTokenListenerImpl.h"

using namespace RuStoreSDK;

DeleteTokenListenerImpl::~DeleteTokenListenerImpl()
{
}

#if PLATFORM_ANDROID
extern "C"
{
    JNIEXPORT void JNICALL Java_ru_rustore_unitysdk_pushclient_wrappers_DeleteTokenListenerWrapper_NativeOnFailure(JNIEnv*, jobject, jlong pointer, jthrowable throwable)
    {
        auto obj = new AndroidJavaObject(throwable);
        obj->UpdateToGlobalRef();

        auto castobj = reinterpret_cast<DeleteTokenListenerImpl*>(pointer);
        castobj->OnFailure(obj);
    }

    JNIEXPORT void JNICALL Java_ru_rustore_unitysdk_pushclient_wrappers_DeleteTokenListenerWrapper_NativeOnSuccess(JNIEnv*, jobject, jlong pointer)
    {
        auto castobj = reinterpret_cast<DeleteTokenListenerImpl*>(pointer);
        castobj->OnSuccess();
    }
}
#endif
