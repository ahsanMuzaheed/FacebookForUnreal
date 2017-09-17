// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "ModuleManager.h"
#include "FacebookIdentityInterface.h"
#include "FacebookSharerInterface.h"
#include "FacebookUtilsInterface.h"

DECLARE_LOG_CATEGORY_EXTERN(UEFB, Log, All);

typedef TSharedPtr<IFacebookIdentityInterface, ESPMode::ThreadSafe> FFacebookIdentityCommonPtr;
typedef TSharedPtr<IFacebookSharerInterface, ESPMode::ThreadSafe> FFacebookSharerCommonPtr;
typedef TSharedPtr<IFacebookUtilsInterface, ESPMode::ThreadSafe> FFacebookUtilsCommonPtr;

class IFacebookForUnreal : public IModuleInterface
{
public:
	static inline IFacebookForUnreal& Get()
	{
		return FModuleManager::LoadModuleChecked< IFacebookForUnreal >("FacebookForUnreal");
	}

	inline FFacebookIdentityCommonPtr GetIdentityInterface() const
	{
		return IdentityInterface;
	}

	inline FFacebookSharerCommonPtr GetSharerInterface() const
	{
		return SharerInterface;
	}

	inline FFacebookUtilsCommonPtr GetUtilsInterface() const
	{
		return UtilsInterface;
	}

	FFacebookIdentityCommonPtr IdentityInterface;
	FFacebookSharerCommonPtr SharerInterface;
	FFacebookUtilsCommonPtr UtilsInterface;
};