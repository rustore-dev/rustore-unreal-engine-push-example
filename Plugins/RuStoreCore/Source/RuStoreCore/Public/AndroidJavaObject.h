// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "JavaMethodSignature.h"
#include "JavaTypeConverter.h"
#include "AndroidJavaLog.h"

namespace RuStoreSDK
{
    class RUSTORECORE_API AndroidJavaObject : public IAndroidClasses
    {
    private:
        FString className = "";
        FString ExtractName();
        bool bIsAttachThread = false;
        bool bIsGlobalRef = true;

    #if PLATFORM_ANDROID
        JNIEnv* env = nullptr;
        jclass javaClass = nullptr;
        jobject javaObject = nullptr;

        static JavaVM* CurrentJavaVM()
        {
            JavaVM* CurrentJavaVM = nullptr;
            FAndroidApplication::GetJavaEnv()->GetJavaVM(&CurrentJavaVM);
            return CurrentJavaVM;
        }
    #endif

    public:
        AndroidJavaObject(FString className, bool bAsGlobalRef = true);
        AndroidJavaObject(FString className, long cppPointer, bool bAsGlobalRef = true);
    #if PLATFORM_ANDROID
        AndroidJavaObject(jthrowable throwable);
        AndroidJavaObject(jobject javaObject);
        AndroidJavaObject(jobject javaObject, FString asInterface);
        AndroidJavaObject(jclass javaClass, jobject javaObject);

        jobject GetJObject();
    #endif

        virtual ~AndroidJavaObject();

        FString GetName() override;

        static AndroidJavaObject* GetStaticAJObject(FString fieldName, FString className);

        template<typename T>
        T* Get(FString fieldName);
        int GetInt(FString fieldName);
        int GetLong(FString fieldName);
        bool GetBool(FString fieldName);
        FString GetFString(FString fieldName);
        int GetEnum(FString fieldName, FString signature);
        TArray<uint8>* GetByteArray(FString fieldName);
        AndroidJavaObject* GetAJObject(FString fieldName, FString signature = "");
        AndroidJavaObject* GetAJObjectArrayElement(int i);
        FString GetFStringArrayElement(int i);

        void SetInterfaceName(FString asInterface);
        bool AttachCurrentThread();
        AndroidJavaObject* UpdateToGlobalRef();

        FString CallJavaClassFString(FString methodName);

        template<typename... Args>
        void CallVoid(FString methodName, Args... args)
        {
    #if PLATFORM_ANDROID
            FString methodSignature = JavaMethodSignature::MakeVoid(args...);
            jmethodID javaMethodID = FJavaWrapper::FindMethod(env, javaClass, TCHAR_TO_ANSI(*methodName), TCHAR_TO_ANSI(*methodSignature), false);
            FJavaWrapper::CallVoidMethod(env, javaObject, javaMethodID, JavaTypeConverter::SetValue(env, args)...);
    #endif
        }

        template<typename... Args>
        unsigned char CallByte(FString methodName, Args... args)
        {
            unsigned char result = 0;
#if PLATFORM_ANDROID
            FString methodSignature = JavaMethodSignature::MakeByte(args...);
            jmethodID javaMethodID = FJavaWrapper::FindMethod(env, javaClass, TCHAR_TO_ANSI(*methodName), TCHAR_TO_ANSI(*methodSignature), false);
            result = (unsigned char)env->CallByteMethod(javaObject, javaMethodID, JavaTypeConverter::SetValue(env, args)...);
#endif
            return result;
        }

        template<typename... Args>
        int CallInt(FString methodName, Args... args)
        {
            int result = 0;
    #if PLATFORM_ANDROID
            FString methodSignature = JavaMethodSignature::MakeInt(args...);
            jmethodID javaMethodID = FJavaWrapper::FindMethod(env, javaClass, TCHAR_TO_ANSI(*methodName), TCHAR_TO_ANSI(*methodSignature), false);
            result = (int)env->CallIntMethod(javaObject, javaMethodID, JavaTypeConverter::SetValue(env, args)...);
    #endif
            return result;
        }

        template<typename... Args>
        int CallLong(FString methodName, Args... args)
        {
            long result = 0;
    #if PLATFORM_ANDROID
            FString methodSignature = JavaMethodSignature::MakeLong(args...);
            jmethodID javaMethodID = FJavaWrapper::FindMethod(env, javaClass, TCHAR_TO_ANSI(*methodName), TCHAR_TO_ANSI(*methodSignature), false);
            result = (long)env->CallLongMethod(javaObject, javaMethodID, JavaTypeConverter::SetValue(env, args)...);
    #endif
            return result;
        }

        template<typename... Args>
        FString CallFString(FString methodName, Args... args)
        {
            FString result = "";
    #if PLATFORM_ANDROID
            FString methodSignature = JavaMethodSignature::MakeFString(args...);
            jmethodID javaMethodID = FJavaWrapper::FindMethod(env, javaClass, TCHAR_TO_ANSI(*methodName), TCHAR_TO_ANSI(*methodSignature), false);

            jstring strResult = (jstring)FJavaWrapper::CallObjectMethod(env, javaObject, javaMethodID, JavaTypeConverter::SetValue(env, args)...);
            result = FJavaHelper::FStringFromParam(env, strResult);
    #endif
            return result;
        }

        template<typename... Args>
        AndroidJavaObject* CallAJClass(FString methodName, Args... args)
        {
            AndroidJavaObject* result = nullptr;
    #if PLATFORM_ANDROID
            FString methodSignature = JavaMethodSignature::MakeAJClass(args...);
            jmethodID javaMethodID = FJavaWrapper::FindMethod(env, javaClass, TCHAR_TO_ANSI(*methodName), TCHAR_TO_ANSI(*methodSignature), false);

            jobject localRef = FJavaWrapper::CallObjectMethod(env, javaObject, javaMethodID, JavaTypeConverter::SetValue(env, args)...);
            result = new AndroidJavaObject(localRef);
            result->UpdateToGlobalRef();
    #endif
            return result;
        }

        template<typename... Args>
        AndroidJavaObject* CallAJObject(FString methodName, Args... args)
        {
            AndroidJavaObject* result = nullptr;
    #if PLATFORM_ANDROID
            FString methodSignature = JavaMethodSignature::MakeAJObject(args...);
            jmethodID javaMethodID = FJavaWrapper::FindMethod(env, javaClass, TCHAR_TO_ANSI(*methodName), TCHAR_TO_ANSI(*methodSignature), false);

            jobject localRef = (jobject)FJavaWrapper::CallObjectMethod(env, javaObject, javaMethodID, JavaTypeConverter::SetValue(env, args)...);
            result = new AndroidJavaObject(localRef);
            result->UpdateToGlobalRef();
    #endif
            return result;
        }

        template<typename... Args>
        TArray<uint8>* CallByteArray(const FString methodName, Args... args)
        {
            TArray<uint8>* result = new TArray<uint8>();
#if PLATFORM_ANDROID
            FString methodSignature = JavaMethodSignature::MakeByteArray(args...);

#ifdef RuStoreDebug
            _LogInfo(RuStoreDebug, signature);
#endif

            jmethodID javaMethodId = env->GetStaticMethodID(javaClass, TCHAR_TO_ANSI(*methodName), TCHAR_TO_ANSI(*methodSignature));
            jbyteArray jArray = (jbyteArray)env->CallObjectMethod(javaClass, javaMethodId, JavaTypeConverter::SetValue(env, args)...);

            int length = env->GetArrayLength(jArray);
            jbyte* data = env->GetByteArrayElements(jArray, nullptr);

            for (int i = 0; i < length; i++)
            {
                result->Add(static_cast<uint8>(data[i]));
            }

            env->ReleaseByteArrayElements(jArray, data, 0);
#endif
            return result;
        }

        template<typename... Args>
        AndroidJavaObject* CallSpecificAJObject(FString methodName, FString signature, Args... args)
        {
            AndroidJavaObject* result = nullptr;
#if PLATFORM_ANDROID
            FString methodSignature = JavaMethodSignature::MakeSpecificAJObject(signature, args...);
            jmethodID javaMethodID = FJavaWrapper::FindMethod(env, javaClass, TCHAR_TO_ANSI(*methodName), TCHAR_TO_ANSI(*methodSignature), false);

            jobject localRef = (jobject)FJavaWrapper::CallObjectMethod(env, javaObject, javaMethodID, JavaTypeConverter::SetValue(env, args)...);
            result = new AndroidJavaObject(localRef);
            result->UpdateToGlobalRef();
#endif
            return result;
        }
    };
}
