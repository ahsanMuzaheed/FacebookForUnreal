// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EActionTypes.generated.h"

UENUM(BlueprintType)
enum class EActionType : uint8
{
	/**
	* Will use the Action Type "games.plays"
	* This will show up on facebook as "<Facebook Name> played <Title of the post>"
	* Only shows on Activity log
	*/
	ACTION_PLAYS = 0,

	/** 
	 * Will use the Action Type "games.celebrate"
	 * <Facebook Name> celebrated a victory in <App name>
	 */
	ACTION_CELEBRATE = 1,

	/**
	* Will use the Action Type "games.saves"
	* <Facebook Name> saved a game on <App name>
	*/
	ACTION_SAVES = 2,

	/**
	* Will use the Action Type "games.achieves"
	*/
	ACTION_ACHIEVES = 3
};

inline const TCHAR* ToString(EActionType actionType)
{
	switch (actionType)
	{
	case EActionType::ACTION_PLAYS:
		return TEXT("ACTION_PLAYS");
	case EActionType::ACTION_CELEBRATE:
		return TEXT("ACTION_CELEBRATE");
	case EActionType::ACTION_SAVES:
		return TEXT("ACTION_SAVES");
	case EActionType::ACTION_ACHIEVES:
		return TEXT("ACTION_ACHIEVES");
	}

	return TEXT("");
}

inline const uint8 ToInt(EActionType actionType)
{
	switch (actionType)
	{
	case EActionType::ACTION_PLAYS:
		return 0;
	case EActionType::ACTION_CELEBRATE:
		return 1;
	case EActionType::ACTION_SAVES:
		return 2;
	case EActionType::ACTION_ACHIEVES:
		return 3;
	}

	return 0;
}

