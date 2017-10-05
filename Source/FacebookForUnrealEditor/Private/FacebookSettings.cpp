// Fill out your copyright notice in the Description page of Project Settings.

#include "FacebookForUnrealEditor.h"
#include "FacebookSettings.h"

#if WITH_EDITOR
void UFacebookSettings::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	//if (!GConfig) return;

	FString SubsystemSection = "OnlineSubsystemFacebook";
	FString IdentitySection = "OnlineSubsystemFacebook.OnlineIdentityFacebook";

	//UProperty* prop = PropertyChangedEvent.Property;

	//FName PropertyName = (prop != nullptr) ? prop->GetFName() : NAME_None;
	//FName PropertyValue = PropertyChangedEvent.Property->Get
	
	//UStrProperty 
	
	//UStrProperty PropertyValue = prop->ContainerPtrToValuePtr

	//GConfig->SetString(
	//	*SubsystemSection,
	//	*PropertyName.ToString(),
	//	TEXT("GwapoSiZob"),
	//	GEngineIni
	//);

	//GConfig->SetString(
	//	*IdentitySection,
	//	TEXT("ScopeFields"),
	//	TEXT("E:\UE4\IsAwesome"),
	//	GEngineIni
	//);

	//GConfig->Flush(false, GEngineIni);

	Super::PostEditChangeProperty(PropertyChangedEvent);
	SaveConfig(CPF_Config, *GetDefaultConfigFilename());

	

}
#endif


