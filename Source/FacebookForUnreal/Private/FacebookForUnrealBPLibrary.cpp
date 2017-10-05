// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FacebookForUnrealBPLibrary.h"
#include "FacebookForUnreal.h"

UFacebookForUnrealBPLibrary::UFacebookForUnrealBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}
void UFacebookForUnrealBPLibrary::FacebookLogout()
{
	IFacebookForUnreal::Get().GetIdentityInterface()->FacebookLogout();
}

bool UFacebookForUnrealBPLibrary::IsFacebookLoggedIn()
{
	return IFacebookForUnreal::Get().GetIdentityInterface()->IsFacebookLoggedIn();
}

FString UFacebookForUnrealBPLibrary::GetFacebookAccessToken()
{
	return IFacebookForUnreal::Get().GetIdentityInterface()->GetFacebookAccessToken();
}

void UFacebookForUnrealBPLibrary::FacebookShareDialog(const FString & title, const FString & description, const FString & imageLink, EActionType actionType)
{
	IFacebookForUnreal::Get().GetSharerInterface()->FacebookShareDialog(title, description, imageLink, actionType);
}

void UFacebookForUnrealBPLibrary::FacebookMessageDialog(const FString & title, const FString & description, const FString & imageLink, EActionType actionType, const FString & link)
{
	IFacebookForUnreal::Get().GetSharerInterface()->FacebookMessageDialog(title, description, imageLink, actionType, link);
}

void UFacebookForUnrealBPLibrary::FacebookGameRequest(const FString & message)
{
	IFacebookForUnreal::Get().GetSharerInterface()->FacebookGameRequest(message);
}

bool UFacebookForUnrealBPLibrary::IsInternetConnected()
{
	return IFacebookForUnreal::Get().GetUtilsInterface()->IsInternetConnected();
}