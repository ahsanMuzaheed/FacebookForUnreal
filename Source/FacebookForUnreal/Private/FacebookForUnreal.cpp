// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FacebookForUnreal.h"
#include "FacebookSharerCommon.h"
#include "FacebookUtilsCommon.h"
#include "FacebookIdentityCommon.h"

#define LOCTEXT_NAMESPACE "FFacebookForUnrealModule"

DEFINE_LOG_CATEGORY(UEFB);

class FFacebookForUnrealModule : public IFacebookForUnreal
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

void FFacebookForUnrealModule::StartupModule()
{

#if PLATFORM_ANDROID || PLATFORM_IOS
	IdentityInterface = MakeShareable(new FFacebookIdentityCommon());
	SharerInterface = MakeShareable(new FFacebookSharerCommon());
	UtilsInterface = MakeShareable(new FFacebookUtilsCommon());
#endif
	
}

void FFacebookForUnrealModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FFacebookForUnrealModule, FacebookForUnreal)