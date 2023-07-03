// Copyright Epic Games, Inc. All Rights Reserved.

#include "GetTokenListenerImpl.h"

using namespace RuStoreSDK;

#if PLATFORM_ANDROID
extern "C"
{
    JNIEXPORT void JNICALL Java_com_Plugins_RuStorePush_GetTokenListenerWrapper_NativeOnSuccess(JNIEnv* env, jobject, jlong pointer, jstring result)
    {
        auto castobj = reinterpret_cast<GetTokenListenerImpl*>(pointer);
        castobj->OnSuccess(JavaTypeConverter::Convert(env, result));
    }

    JNIEXPORT void JNICALL Java_com_Plugins_RuStorePush_GetTokenListenerWrapper_NativeOnFailure(JNIEnv*, jobject, jlong pointer, jthrowable throwable)
    {
        auto obj = new AndroidJavaObject(throwable);
        obj->UpdateToGlobalRef();

        auto castobj = reinterpret_cast<GetTokenListenerImpl*>(pointer);
        castobj->OnFailure(obj);
    }
}
#endif
