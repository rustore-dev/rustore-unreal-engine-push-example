// Copyright Epic Games, Inc. All Rights Reserved.

#include "LogListenerImpl.h"
#include "CallbackHandler.h"

using namespace RuStoreSDK;

void LogListenerImpl::OnLogVerbose(FString message, AndroidJavaObject* errorObject)
{
    auto error = TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>(ErrorConverter::Convert(errorObject));
    delete errorObject;

    auto listener = GetWeakPtr();
    CallbackHandler::AddCallback([this, listener, message, error]() {
        if (listener.IsValid())
        {
            this->_onLogVerbose(this->GetId(), message, error);
        }
    });
}

void LogListenerImpl::OnLogDebug(FString message, AndroidJavaObject* errorObject)
{
    auto error = TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>(ErrorConverter::Convert(errorObject));
    delete errorObject;

    auto listener = GetWeakPtr();
    CallbackHandler::AddCallback([this, listener, message, error]() {
        if (listener.IsValid())
        {
            this->_onLogDebug(this->GetId(), message, error);
        }
    });
}

void LogListenerImpl::OnLogInfo(FString message, AndroidJavaObject* errorObject)
{
    auto error = TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>(ErrorConverter::Convert(errorObject));
    delete errorObject;

    auto listener = GetWeakPtr();
    CallbackHandler::AddCallback([this, listener, message, error]() {
        if (listener.IsValid())
        {
            this->_onLogInfo(this->GetId(), message, error);
        }
    });
}

void LogListenerImpl::OnLogWarning(FString message, AndroidJavaObject* errorObject)
{
    auto error = TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>(ErrorConverter::Convert(errorObject));
    delete errorObject;

    auto listener = GetWeakPtr();
    CallbackHandler::AddCallback([this, listener, message, error]() {
        if (listener.IsValid())
        {
            this->_onLogWarning(this->GetId(), message, error);
        }
    });
}

void LogListenerImpl::OnLogError(FString message, AndroidJavaObject* errorObject)
{
    auto error = TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>(ErrorConverter::Convert(errorObject));
    delete errorObject;

    auto listener = GetWeakPtr();
    CallbackHandler::AddCallback([this, listener, message, error]() {
        if (listener.IsValid())
        {
            this->_onLogError(this->GetId(), message, error);
        }
    });
}

#if PLATFORM_ANDROID
extern "C"
{
    JNIEXPORT void JNICALL Java_ru_rustore_unreal_pushclient_wrappers_LogListenerWrapper_NativeLogVerbose(JNIEnv* env, jobject, jlong pointer, jstring message, jthrowable throwable)
    {
        auto obj = new AndroidJavaObject(throwable);
        obj->UpdateToGlobalRef();

        auto castobj = reinterpret_cast<LogListenerImpl*>(pointer);
        castobj->OnLogVerbose(JavaTypeConverter::Convert(env, message), obj);
    }

    JNIEXPORT void JNICALL Java_ru_rustore_unreal_pushclient_wrappers_LogListenerWrapper_NativeLogDebug(JNIEnv* env, jobject, jlong pointer, jstring message, jthrowable throwable)
    {
        auto obj = new AndroidJavaObject(throwable);
        obj->UpdateToGlobalRef();

        auto castobj = reinterpret_cast<LogListenerImpl*>(pointer);
        castobj->OnLogDebug(JavaTypeConverter::Convert(env, message), obj);
    }

    JNIEXPORT void JNICALL Java_ru_rustore_unreal_pushclient_wrappers_LogListenerWrapper_NativeLogInfo(JNIEnv* env, jobject, jlong pointer, jstring message, jthrowable throwable)
    {
        auto obj = new AndroidJavaObject(throwable);
        obj->UpdateToGlobalRef();

        auto castobj = reinterpret_cast<LogListenerImpl*>(pointer);
        castobj->OnLogInfo(JavaTypeConverter::Convert(env, message), obj);
    }

    JNIEXPORT void JNICALL Java_ru_rustore_unreal_pushclient_wrappers_LogListenerWrapper_NativeLogWarning(JNIEnv* env, jobject, jlong pointer, jstring message, jthrowable throwable)
    {
        auto obj = new AndroidJavaObject(throwable);
        obj->UpdateToGlobalRef();

        auto castobj = reinterpret_cast<LogListenerImpl*>(pointer);
        castobj->OnLogWarning(JavaTypeConverter::Convert(env, message), obj);
    }

    JNIEXPORT void JNICALL Java_ru_rustore_unreal_pushclient_wrappers_LogListenerWrapper_NativeLogError(JNIEnv* env, jobject, jlong pointer, jstring message, jthrowable throwable)
    {
        auto obj = new AndroidJavaObject(throwable);
        obj->UpdateToGlobalRef();

        auto castobj = reinterpret_cast<LogListenerImpl*>(pointer);
        castobj->OnLogError(JavaTypeConverter::Convert(env, message), obj);
    }
}
#endif
