// Some copyright should be here...

using System.IO;
using UnrealBuildTool;

public class FacebookForUnrealEditor : ModuleRules
{
    public FacebookForUnrealEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PublicIncludePaths.AddRange( new string[] { "FacebookForUnrealEditor/Public" });

        PrivateIncludePaths.AddRange( new string[] { "FacebookForUnrealEditor/Private" });
        
        PublicDependencyModuleNames.AddRange(new string[] { "FacebookForUnreal" });

        PublicDependencyModuleNames.AddRange(new string[] { "Core" });

        PrivateDependencyModuleNames.AddRange( new string[] 
            {
                "Core",
                "CoreUObject",
                //"InputCore",
                "UnrealEd",
                "Engine",
                "Slate",
                "SlateCore",
                //"EditorStyle",
                //"EditorWidgets",
                //"DesktopWidgets",
                //"PropertyEditor",
                //"SharedSettingsWidgets",
                //"SourceControl",
                //"AndroidRuntimeSettings",
                //"AndroidDeviceDetection",
                //"TargetPlatform",
                //"RenderCore",
                //"MaterialShaderQualitySettings"
            });
        
    }
}
