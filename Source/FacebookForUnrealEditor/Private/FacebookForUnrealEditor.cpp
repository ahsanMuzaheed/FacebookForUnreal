
#include "FacebookForUnrealEditor.h"
#include "FacebookSettings.h"

#include "ISettingsModule.h"

IMPLEMENT_MODULE(FFacebookForUnrealEditorModule, FacebookForUnrealEditor);

#define LOCTEXT_NAMESPACE "FFacebookForUnrealEditorModule"

void FFacebookForUnrealEditorModule::StartupModule()
{
	ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");

	if (SettingsModule != nullptr)
	{
		SettingsModule->RegisterSettings(TEXT("Project"), TEXT("Facebook"), TEXT("Facebook Settings"),
			LOCTEXT("Facebook Settings", "Facebook Settings"),
			LOCTEXT("Facebook Settings", "Settings for Facebook"),
			GetMutableDefault<UFacebookSettings>()
		);
	}
}

void FFacebookForUnrealEditorModule::ShutdownModule()
{

}

#undef LOCTEXT_NAMESPACE