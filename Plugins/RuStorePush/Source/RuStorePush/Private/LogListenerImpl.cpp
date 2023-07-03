// Copyright Epic Games, Inc. All Rights Reserved.

#include "LogListenerImpl.h"
#include "CallbackHandler.h"

using namespace RuStoreSDK;

void LogListenerImpl::OnLog(FString logString)
{
    auto listener = GetWeakPtr();
    CallbackHandler::AddCallback([this, listener, logString]() {
        if (listener.IsValid())
        {
            this->_onLog(this->GetId(), logString);
        }
    });
}

void LogListenerImpl::OnLogWarning(FString logString)
{
    auto listener = GetWeakPtr();
    CallbackHandler::AddCallback([this, listener, logString]() {
        if (listener.IsValid())
        {
            this->_onLogWarning(this->GetId(), logString);
        }
    });
}

void LogListenerImpl::OnLogError(FString logString)
{
    auto listener = GetWeakPtr();
    CallbackHandler::AddCallback([this, listener, logString]() {
        if (listener.IsValid())
        {
            this->_onLogError(this->GetId(), logString);
        }
    });
}

void LogListenerImpl::OnLogException(AndroidJavaObject* errorObject)
{
    auto error = TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>(ErrorConverter::Convert(errorObject));
    delete errorObject;

    auto listener = GetWeakPtr();
    CallbackHandler::AddCallback([this, listener, error]() {
        if (listener.IsValid())
        {
            this->_onLogException(this->GetId(), error);
        }
    });
}

#if PLATFORM_ANDROID
extern "C"
{
    JNIEXPORT void JNICALL Java_com_Plugins_RuStorePush_LogListenerWrapper_NativeLog(JNIEnv* env, jobject, jlong pointer, jstring logString)
    {
        auto castobj = reinterpret_cast<LogListenerImpl*>(pointer);
        castobj->OnLog(JavaTypeConverter::Convert(env, logString));
    }

    JNIEXPORT void JNICALL Java_com_Plugins_RuStorePush_LogListenerWrapper_NativeLogWarning(JNIEnv* env, jobject, jlong pointer, jstring logString)
    {
        auto castobj = reinterpret_cast<LogListenerImpl*>(pointer);
        castobj->OnLogWarning(JavaTypeConverter::Convert(env, logString));
    }

    JNIEXPORT void JNICALL Java_com_Plugins_RuStorePush_LogListenerWrapper_NativeLogError(JNIEnv* env, jobject, jlong pointer, jstring logString)
    {
        auto castobj = reinterpret_cast<LogListenerImpl*>(pointer);
        castobj->OnLogError(JavaTypeConverter::Convert(env, logString));
    }

    JNIEXPORT void JNICALL Java_com_Plugins_RuStorePush_LogListenerWrapper_NativeLogException(JNIEnv*, jobject, jlong pointer, jthrowable throwable)
    {
        auto obj = new AndroidJavaObject(throwable);
        obj->UpdateToGlobalRef();

        auto castobj = reinterpret_cast<LogListenerImpl*>(pointer);
        castobj->OnLogException(obj);
    }
}
#endif
