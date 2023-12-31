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
		long GetLong(FString fieldName);
		bool GetBool(FString fieldName);
		FString GetFString(FString fieldName);
		int GetEnum(FString fieldName, FString signature);
		TArray<uint8>* GetByteArray(FString fieldName);
		AndroidJavaObject* GetAJObject(FString fieldName, FString signature = "");
		AndroidJavaObject* GetAJObjectArrayElement(int i);
		FString GetFStringArrayElement(int i);
		FString ConvertToFString();

		void SetInterfaceName(FString asInterface);
		bool AttachCurrentThread();
		AndroidJavaObject* UpdateToGlobalRef();

		FString CallJavaClassFString(FString methodName);

		template<typename... Args>
		void CallVoid(FString methodName, Args... args)
		{
#if PLATFORM_ANDROID
			FString methodSignature = JavaMethodSignature::MakeVoid(args...);

#ifdef RuStoreDebug
			_LogInfo(RuStoreDebug, methodSignature);
#endif

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

#ifdef RuStoreDebug
			_LogInfo(RuStoreDebug, methodSignature);
#endif

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

#ifdef RuStoreDebug
			_LogInfo(RuStoreDebug, methodSignature);
#endif

			result = (int)env->CallIntMethod(javaObject, javaMethodID, JavaTypeConverter::SetValue(env, args)...);
#endif

			return result;
		}

		template<typename... Args>
		long CallLong(FString methodName, Args... args)
		{
			long result = 0;

#if PLATFORM_ANDROID
			FString methodSignature = JavaMethodSignature::MakeLong(args...);
			jmethodID javaMethodID = FJavaWrapper::FindMethod(env, javaClass, TCHAR_TO_ANSI(*methodName), TCHAR_TO_ANSI(*methodSignature), false);

#ifdef RuStoreDebug
			_LogInfo(RuStoreDebug, methodSignature);
#endif

			result = (long)env->CallLongMethod(javaObject, javaMethodID, JavaTypeConverter::SetValue(env, args)...);
#endif

			return result;
		}

		template<typename... Args>
		float CallFloat(FString methodName, Args... args)
		{
			float result = 0;

#if PLATFORM_ANDROID
			FString methodSignature = JavaMethodSignature::MakeFloat(args...);
			jmethodID javaMethodID = FJavaWrapper::FindMethod(env, javaClass, TCHAR_TO_ANSI(*methodName), TCHAR_TO_ANSI(*methodSignature), false);

#ifdef RuStoreDebug
			_LogInfo(RuStoreDebug, methodSignature);
#endif

			result = (float)env->CallFloatMethod(javaObject, javaMethodID, JavaTypeConverter::SetValue(env, args)...);
#endif

			return result;
		}

		template<typename... Args>
		float CallDouble(FString methodName, Args... args)
		{
			double result = 0;

#if PLATFORM_ANDROID
			FString methodSignature = JavaMethodSignature::MakeDouble(args...);
			jmethodID javaMethodID = FJavaWrapper::FindMethod(env, javaClass, TCHAR_TO_ANSI(*methodName), TCHAR_TO_ANSI(*methodSignature), false);

#ifdef RuStoreDebug
			_LogInfo(RuStoreDebug, methodSignature);
#endif

			result = (double)env->CallDoubleMethod(javaObject, javaMethodID, JavaTypeConverter::SetValue(env, args)...);
#endif

			return result;
		}

		template<typename... Args>
		bool CallBool(FString methodName, Args... args)
		{
			bool result = false;

#if PLATFORM_ANDROID
			FString methodSignature = JavaMethodSignature::MakeBool(args...);
			jmethodID javaMethodID = FJavaWrapper::FindMethod(env, javaClass, TCHAR_TO_ANSI(*methodName), TCHAR_TO_ANSI(*methodSignature), false);

#ifdef RuStoreDebug
			_LogInfo(RuStoreDebug, methodSignature);
#endif

			result = (bool)env->CallBooleanMethod(javaObject, javaMethodID, JavaTypeConverter::SetValue(env, args)...);
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

#ifdef RuStoreDebug
			_LogInfo(RuStoreDebug, methodSignature);
#endif

			jstring strResult = (jstring)FJavaWrapper::CallObjectMethod(env, javaObject, javaMethodID, JavaTypeConverter::SetValue(env, args)...);
			result = FJavaHelper::FStringFromParam(env, strResult);
#endif

			return result;
		}

		template<typename... Args>
		TArray<uint8>* CallByteArray(FString methodName, Args... args)
		{
			TArray<uint8>* result = nullptr;

#if PLATFORM_ANDROID
			FString methodSignature = JavaMethodSignature::MakeByteArray(args...);
			jmethodID javaMethodID = FJavaWrapper::FindMethod(env, javaClass, TCHAR_TO_ANSI(*methodName), TCHAR_TO_ANSI(*methodSignature), false);

#ifdef RuStoreDebug
			_LogInfo(RuStoreDebug, methodSignature);
#endif

			jbyteArray jArray = (jbyteArray)FJavaWrapper::CallObjectMethod(env, javaObject, javaMethodID, JavaTypeConverter::SetValue(env, args)...);
			if (jArray != nullptr)
			{
				int length = env->GetArrayLength(jArray);
				jbyte* data = env->GetByteArrayElements(jArray, nullptr);

				result = new TArray<uint8>();
				for (int i = 0; i < length; i++)
				{
					result->Add(static_cast<uint8>(data[i]));
				}
				env->ReleaseByteArrayElements(jArray, data, 0);
			}
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

#ifdef RuStoreDebug
			_LogInfo(RuStoreDebug, methodSignature);
#endif

            jobject localRef = FJavaWrapper::CallObjectMethod(env, javaObject, javaMethodID, JavaTypeConverter::SetValue(env, args)...);
			if (localRef != nullptr)
			{
				result = new AndroidJavaObject(localRef);
				result->UpdateToGlobalRef();
			}
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

#ifdef RuStoreDebug
			_LogInfo(RuStoreDebug, methodSignature);
#endif

            jobject localRef = (jobject)FJavaWrapper::CallObjectMethod(env, javaObject, javaMethodID, JavaTypeConverter::SetValue(env, args)...);
			if (localRef != nullptr)
			{
				result = new AndroidJavaObject(localRef);
				result->UpdateToGlobalRef();
			}
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

#ifdef RuStoreDebug
			_LogInfo(RuStoreDebug, methodSignature);
#endif

			jobject localRef = (jobject)FJavaWrapper::CallObjectMethod(env, javaObject, javaMethodID, JavaTypeConverter::SetValue(env, args)...);
			if (localRef != nullptr)
			{
				result = new AndroidJavaObject(localRef);
				result->UpdateToGlobalRef();
			}
#endif

            return result;
        }
    };
}
