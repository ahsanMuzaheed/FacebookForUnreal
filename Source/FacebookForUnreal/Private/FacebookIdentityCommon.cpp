// Fill out your copyright notice in the Description page of Project Settings.

#include "FacebookIdentityCommon.h"

#if PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#include "Android/AndroidApplication.h"
#include <android_native_app_glue.h>


static jmethodID FacebookGetAccessTokenMethod;
#endif

#define CHECK_JNI_METHOD(Id) checkf(Id != nullptr, TEXT("Failed to find " #Id));

FFacebookIdentityCommon::FFacebookIdentityCommon()
{
	UE_LOG(UEFB, Warning, TEXT("%s"), TEXT("Initializing FacebookIdentityCommon"));
	Init();

#if PLATFORM_ANDROID
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		FacebookGetAccessTokenMethod = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_Facebook_GetAccessToken", "()Ljava/lang/String;", false);
		CHECK_JNI_METHOD(FacebookGetAccessTokenMethod);
	}
#endif
}

FFacebookIdentityCommon::~FFacebookIdentityCommon()
{
}

void FFacebookIdentityCommon::Init()
{
	UE_LOG(UEFB, Warning, TEXT("%s"), TEXT("Init Subsystem"));

	FBSubsystem = IOnlineSubsystem::Get(TEXT("FACEBOOK"));

	// Init Subsystem
	FBSubsystem->Init();
	UE_LOG(UEFB, Warning, TEXT("%s"), TEXT("Subsystem Initialization Complete"));
}

void FFacebookIdentityCommon::FacebookLogin()
{
	UE_LOG(UEFB, Warning, TEXT("%s"), TEXT("Called FacebookLogin in FacebookIdentityCommon"));
	//Use native subsystems' login
	FBSubsystem->GetIdentityInterface()->Login(0, *(new FOnlineAccountCredentials));
}

void FFacebookIdentityCommon::FacebookLogout()
{
	UE_LOG(UEFB, Warning, TEXT("%s"), TEXT("Called FacebookLogout in FacebookIdentityCommon"));
	FBSubsystem->GetIdentityInterface()->Logout(0);
}

FString FFacebookIdentityCommon::GetFacebookAccessToken()
{
	UE_LOG(UEFB, Warning, TEXT("%s"), TEXT("Called GetFacebookAuthToken in FacebookIdentityCommon"));
#if PLATFORM_ANDROID
	extern FString AndroidThunkCpp_FacebookGetAccessToken();
	return AndroidThunkCpp_FacebookGetAccessToken();
#endif
	return "No Access Token!";
}

bool FFacebookIdentityCommon::IsFacebookLoggedIn()
{
	UE_LOG(UEFB, Warning, TEXT("%s"), TEXT("Called IsFacebookLoggedIn in FacebookIdentityCommon"));
	ELoginStatus::Type LoginStatus = FBSubsystem->GetIdentityInterface()->GetLoginStatus(0);
	if (LoginStatus == ELoginStatus::LoggedIn)
	{
		return true;
	}

	return false;
}

inline IOnlineSubsystem* FFacebookIdentityCommon::GetFbSubsystem()
{
	return FBSubsystem;
}

/************************************************************************/
/*	Implementation of Android Thunk Functions							*/
/************************************************************************/


#if PLATFORM_ANDROID

FString AndroidThunkCpp_FacebookGetAccessToken()
{
	UE_LOG_ONLINE(Verbose, TEXT("AndroidThunkCpp_FacebookGetAccessToken"));

	FString AccessToken;
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{

		jstring accessToken = (jstring)FJavaWrapper::CallObjectMethod(Env, FJavaWrapper::GameActivityThis, FacebookGetAccessTokenMethod);

		const char* charsAccessToken = Env->GetStringUTFChars(accessToken, 0);
		AccessToken = FString(UTF8_TO_TCHAR(charsAccessToken));
		Env->ReleaseStringUTFChars(accessToken, charsAccessToken);
		Env->DeleteLocalRef(accessToken);
	}

	return AccessToken;
}

#endif