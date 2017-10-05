// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/FacebookIdentityInterface.h"
#include "Online.h"

/**
 * Facebook integration of Facebook user's identity
 */

class FFacebookIdentityCommon : public IFacebookIdentityInterface
{

public:
	FFacebookIdentityCommon();
	virtual ~FFacebookIdentityCommon();

	virtual void Init();

	virtual void FacebookLogin() override;

	virtual void FacebookLogout() override;

	virtual FString GetFacebookAccessToken() override;

	virtual bool IsFacebookLoggedIn() override;

	virtual IOnlineSubsystem* GetFbSubsystem() override;

	virtual FString GetLoginStatusString(ELoginStatus::Type EnumValue);

	//DEFINE_UEFB_DELEGATE_ONE_PARAM(LoginComplete, FString);

protected:
	IOnlineSubsystem* FBSubsystem;

};
