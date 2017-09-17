// Fill out your copyright notice in the Description page of Project Settings.

#include "FacebookSharerCommon.h"

#if PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#include "Android/AndroidApplication.h"
#include <android_native_app_glue.h>


static jmethodID FacebookShareDialogMethod;
static jmethodID FacebookMessageDialogMethod;
static jmethodID FacebookGameRequestMethod;
#endif

// Log_Facebook implementation
DEFINE_LOG_CATEGORY(LogFacebook);
#define CHECK_JNI_METHOD(Id) checkf(Id != nullptr, TEXT("Failed to find " #Id));

FFacebookSharerCommon::FFacebookSharerCommon()
{
	//UE_LOG_ONLINE(Warning, TEXT("Finding thunk methods"));

#if PLATFORM_ANDROID
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{

		FacebookShareDialogMethod = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_Facebook_ShareDialog", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;I)V", false);
		FacebookMessageDialogMethod = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_Facebook_MessageDialog", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;I)V", false);
		FacebookGameRequestMethod = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_Facebook_GameRequest", "(Ljava/lang/String;)V", false);
		CHECK_JNI_METHOD(FacebookShareDialogMethod);
		CHECK_JNI_METHOD(FacebookMessageDialogMethod);
		CHECK_JNI_METHOD(FacebookGameRequestMethod);

		if (FacebookMessageDialogMethod || FacebookShareDialogMethod || FacebookGameRequestMethod)
		{
			//UE_LOG("UE4", DEBUG, "Found FacebookShare java methods");
		}
	}
#endif
}

FFacebookSharerCommon::~FFacebookSharerCommon()
{
}

void FFacebookSharerCommon::FacebookShareDialog(const FString& title, const FString& description, const FString& imageLink, EActionType actionType)
{
	FFacebookSharerCommon::AndroidThunkCpp_Facebook_ShareDialog(title, description, imageLink, actionType);
}

void FFacebookSharerCommon::FacebookMessageDialog(const FString& title, const FString& description, const FString& imageLink, EActionType actionType)
{
	FFacebookSharerCommon::AndroidThunkCpp_Facebook_MessageDialog(title, description, imageLink, actionType);
}

void FFacebookSharerCommon::FacebookGameRequest(const FString& message)
{
	FFacebookSharerCommon::AndroidThunkCpp_Facebook_GameRequest(message);
}


/************************************************************************/
/*	Implementation of Android Thunk Functions							*/
/************************************************************************/


void FFacebookSharerCommon::AndroidThunkCpp_Facebook_ShareDialog(const FString& title, const FString& description, const FString& imageLink, EActionType actionType)
{
#if PLATFORM_ANDROID
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		// Creating java readable variables from parameters
		jstring jTitle = Env->NewStringUTF(TCHAR_TO_UTF8(*title));
		jstring jDescription = Env->NewStringUTF(TCHAR_TO_UTF8(*description));
		jstring jImageLink = Env->NewStringUTF(TCHAR_TO_UTF8(*imageLink));

		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, FacebookShareDialogMethod, 
			jTitle, jDescription, jImageLink, ToInt(actionType));

		// clean up references
		Env->DeleteLocalRef(jTitle);
		Env->DeleteLocalRef(jDescription);
		Env->DeleteLocalRef(jImageLink);
	}
#endif
}

void FFacebookSharerCommon::AndroidThunkCpp_Facebook_MessageDialog(const FString& title, const FString& description, const FString& imageLink, EActionType actionType)
{
#if PLATFORM_ANDROID
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		// Creating java readable variables from parameters
		jstring jTitle = Env->NewStringUTF(TCHAR_TO_UTF8(*title));
		jstring jDescription = Env->NewStringUTF(TCHAR_TO_UTF8(*description));
		jstring jImageLink = Env->NewStringUTF(TCHAR_TO_UTF8(*imageLink));

		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, FacebookMessageDialogMethod,
			jTitle, jDescription, jImageLink, ToInt(actionType));

		// clean up references
		Env->DeleteLocalRef(jTitle);
		Env->DeleteLocalRef(jDescription);
		Env->DeleteLocalRef(jImageLink);
	}
#endif
}

void FFacebookSharerCommon::AndroidThunkCpp_Facebook_GameRequest(const FString& message)
{
#if PLATFORM_ANDROID
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		// Creating java readable variables from parameters
		jstring jMessage = Env->NewStringUTF(TCHAR_TO_UTF8(*message));

		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, FacebookGameRequestMethod, jMessage);

		// clean up references
		Env->DeleteLocalRef(jMessage);
	}
#endif
}