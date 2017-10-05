// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FacebookSettings.generated.h"

/**
 * 
 */
UCLASS(transient, config = Engine)
class UFacebookSettings : public UObject
{
	GENERATED_BODY()

	UPROPERTY(Config, EditAnywhere, Category = Facebook, Meta = (DisplayName = "Facebook Client Id"))
		FString ClientId;

	UPROPERTY(Config, EditAnywhere, Category = Facebook, Meta = (DisplayName = "Facebook Open Graph Link"))
		FString ShareLink;
	
#if WITH_EDITOR
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
	
};
