#pragma once

#include "ModuleManager.h"

class FToolBarBuilder;
class FMenuBuilder;

class FFacebookForUnrealEditorModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

};