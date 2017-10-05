// Fill out your copyright notice in the Description page of Project Settings.

#include "LoginCallback.h"
#include "FacebookForUnreal.h"
#include "FacebookIdentityCommon.h"

ULoginCallback::ULoginCallback()
{
}

ULoginCallback::~ULoginCallback()
{
}
	
ULoginCallback* ULoginCallback::FacebookLogin()
{
	UE_LOG(FacebookForUnrealLog, Warning, TEXT("%s"), TEXT("Called FacebookLogin in LoginCallback"));

	ULoginCallback* proxy = NewObject<ULoginCallback>();

	return proxy;
}

void ULoginCallback::Activate()
{
	UE_LOG(FacebookForUnrealLog, Warning, TEXT("%s"), TEXT("Called Activate in LoginCallback"));
	IOnlineSubsystem* FbSubsLoc = IFacebookForUnreal::Get().GetIdentityInterface()->GetFbSubsystem();

	IdentityPtr = FbSubsLoc->GetIdentityInterface();

	//Assign Delegate Function to handle login
	IdentityPtr->AddOnLoginCompleteDelegate_Handle(0, FOnLoginCompleteDelegate::CreateUObject(this, &ULoginCallback::ReturnAccessToken));

	UE_LOG(FacebookForUnrealLog, Warning, TEXT("%s"), TEXT("Will now start calling FacebookLogin within Activate"));

	IFacebookForUnreal::Get().GetIdentityInterface()->FacebookLogin();
}


void ULoginCallback::ReturnAccessToken(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Error)
{
	UE_LOG(FacebookForUnrealLog, Warning, TEXT("%s"), TEXT("Called ReturnAccessToken in LoginCallback"));

	//Returns AuthToken
	FString AccessToken = IFacebookForUnreal::Get().GetIdentityInterface()->GetFacebookAccessToken();

	if (AccessToken.IsEmpty()) {
		UE_LOG(FacebookForUnrealLog, Warning, TEXT("%s"), TEXT("ReturnAccessToken OnFailure"));
		OnFailure.Broadcast("No Access Token!");
	} 
	else
	{
		UE_LOG(FacebookForUnrealLog, Warning, TEXT("%s"), TEXT("ReturnAccessToken OnSuccess"));

		//Broadcast this delegate which will contain the AuthToken to be used by the GSFacebookConnectRequest node
		OnSuccess.Broadcast(AccessToken);
	}
}