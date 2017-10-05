 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/FacebookSharerInterface.h"
#include "EActionTypes.h"

/** Facebook integration of sharing posts to Facebook */
class FFacebookSharerCommon : public IFacebookSharerInterface
{
public:
	FFacebookSharerCommon();
	virtual ~FFacebookSharerCommon();

	/** Calls Facebook ShareDialog to share a post to facebook */
	virtual void FacebookShareDialog(const FString& title, const FString& description, const FString& imageLink, EActionType actionType) override;
	
	/** Calls Facebook MessageDialog to share a post to facebook */
	virtual void FacebookMessageDialog(const FString& title, const FString& description, const FString& imageLink, EActionType actionType, const FString& link) override;
	
	/** Calls Facebook GameRequestDialog to send a friend a game invite */
	virtual void FacebookGameRequest(const FString& message) override;

	void AndroidThunkCpp_Facebook_ShareDialog(const FString& title, const FString& description, const FString& imageLink, EActionType actionType);
	void AndroidThunkCpp_Facebook_MessageDialog(const FString& title, const FString& description, const FString& imageLink, EActionType actionType, const FString& link);
	void AndroidThunkCpp_Facebook_GameRequest(const FString& message);

};
