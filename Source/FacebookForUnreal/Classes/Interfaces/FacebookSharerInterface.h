// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EActionTypes.h"
#include "LogDeclaration.h"
//#include "FacebookMobileInterface.generated.h"

class IFacebookSharerInterface
{
public:
	virtual void FacebookShareDialog(const FString& title, const FString& description, const FString& imageLink, EActionType actionType) = 0;

	virtual void FacebookMessageDialog(const FString& title, const FString& description, const FString& imageLink, EActionType actionType) = 0;

	virtual void FacebookGameRequest(const FString& message) = 0;
	
};
