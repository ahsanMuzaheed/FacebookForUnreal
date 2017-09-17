// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/FacebookUtilsInterface.h"

/**
 * 
 */
class FFacebookUtilsCommon : public IFacebookUtilsInterface
{
public:
	FFacebookUtilsCommon();
	virtual ~FFacebookUtilsCommon();

	virtual bool IsInternetConnected() override;
};
