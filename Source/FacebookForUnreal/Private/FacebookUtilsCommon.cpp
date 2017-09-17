// Fill out your copyright notice in the Description page of Project Settings.

#include "FacebookUtilsCommon.h"

#if PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#include "Android/AndroidApplication.h"
#include <android_native_app_glue.h>


static jmethodID IsInternetConnectedMethod;
#endif

#define CHECK_JNI_METHOD(Id) checkf(Id != nullptr, TEXT("Failed to find " #Id));

FFacebookUtilsCommon::FFacebookUtilsCommon()
{
#if PLATFORM_ANDROID
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		IsInternetConnectedMethod = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_IsInternetConnected", "()Z", false);
		CHECK_JNI_METHOD(IsInternetConnectedMethod);
	}
#endif
}

FFacebookUtilsCommon::~FFacebookUtilsCommon()
{
}

bool FFacebookUtilsCommon::IsInternetConnected()
{
	UE_LOG(UEFB, Warning, TEXT("%s"), TEXT("Called IsInternetConnected on FacebookUtilsCommon"));
#if PLATFORM_ANDROID
	extern bool AndroidThunkCpp_IsInternetConnected();
	return AndroidThunkCpp_IsInternetConnected();
#endif
	return false;
}

/************************************************************************/
/*	Implementation of Android Thunk Functions							*/
/************************************************************************/

#if PLATFORM_ANDROID

bool AndroidThunkCpp_IsInternetConnected()
{
	UE_LOG(UEFB, Warning, TEXT("%s"), TEXT("AndroidThunkCpp_IsInternetConnected"));

	bool bIsConnected = false;
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		bIsConnected = FJavaWrapper::CallBooleanMethod(Env, FJavaWrapper::GameActivityThis, IsInternetConnectedMethod);
	}
	return bIsConnected;
}

#endif