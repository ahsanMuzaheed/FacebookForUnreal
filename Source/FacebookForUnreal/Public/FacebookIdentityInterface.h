// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Online.h"
#include "OnlineSubsystem.h"

/**
 * 
 */

DECLARE_MULTICAST_DELEGATE_OneParam(FLoginComplete, FString);
typedef FLoginComplete::FDelegate FLoginCompleteDelegate;

#define DEFINE_UEFB_DELEGATE_BASE(DelegateName) \
public: \
	F##DelegateName DelegateName##Delegates; \
	virtual FDelegateHandle Add##DelegateName##DelegateHandle(const F##DelegateName##Delegate& Delegate) \
	{ \
		DelegateName##Delegates.Add(Delegate); \
		return Delegate.GetHandle(); \
	} \
	virtual void Clear##DelegateName##Delegate_Handle(FDelegateHandle& Handle) \
	{ \
		DelegateName##Delegates.Remove(Handle); \
		Handle.Reset(); \
	}\
	virtual void ClearAll##DelegateName##Delegate_Handle() \
	{ \
		DelegateName##Delegates.Clear(); \
	}

#define DEFINE_UEFB_DELEGATE_ONE_PARAM(DelegateName, Param1Type) \
	DEFINE_UEFB_DELEGATE_BASE(DelegateName) \
	virtual void Trigger##DelegateName##Delegates(Param1Type Param1) \
	{ \
		DelegateName##Delegates.Broadcast(Param1); \
	}



class IFacebookIdentityInterface
{
public:
	virtual void FacebookLogin() = 0;

	virtual void FacebookLogout() = 0;

	virtual FString GetFacebookAccessToken() = 0;

	virtual bool IsFacebookLoggedIn() = 0;

	virtual IOnlineSubsystem* GetFbSubsystem() = 0;
};
