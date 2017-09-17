// Some copyright should be here...

using System.IO;
using UnrealBuildTool;

public class FacebookForUnreal : ModuleRules
{
    public FacebookForUnreal(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        string EnginePath = Path.GetFullPath(BuildConfiguration.RelativeEnginePath);
        string FacebookSdkPath = EnginePath + "Plugins/Online/OnlineSubsystemFacebook/Source/ThirdParty/Android/NotForLicensees/FacebookSDK/";


        if (Directory.Exists(FacebookSdkPath))
        {
            System.Console.WriteLine("Directory for OnlineSubsystemFacebook already exists");
            // Do nothing
        }
        else
        {
            System.Console.WriteLine("Creating directory for OnlineSubsystemFacebook");
            Directory.CreateDirectory(FacebookSdkPath);
        }


        PublicIncludePaths.AddRange( new string[] 
            {
                "FacebookForUnreal/Public"
            });


        PrivateIncludePaths.AddRange( new string[] { "FacebookForUnreal/Private" });


        PublicDependencyModuleNames.AddRange(new string[]
            {
                "Core",
                "OnlineSubsystem",
                "OnlineSubsystemFacebook"
            });


        PrivateDependencyModuleNames.AddRange( new string[] 
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "OnlineSubsystem",
                "OnlineSubsystemFacebook"
            });


        DynamicallyLoadedModuleNames.AddRange(
            new string[] { });

        if (Target.Platform == UnrealTargetPlatform.Android)
        {
            System.Console.WriteLine("Loading FacebookForUnreal_UPL");


            string PluginPath = Utils.MakePathRelativeTo(ModuleDirectory, BuildConfiguration.RelativeEnginePath);
            AdditionalPropertiesForReceipt.Add(new ReceiptProperty("AndroidPlugin", Path.Combine(PluginPath, "FacebookForUnreal_UPL.xml")));
        }



        //Add IOS if you're using it
        if ((Target.Platform == UnrealTargetPlatform.Win32) || (Target.Platform == UnrealTargetPlatform.Win64))
        {
            //Facebook API
            PublicDependencyModuleNames.AddRange(new string[] { "Facebook" });

            //Include
            PublicIncludePaths.Add("OnlineSubsystemFacebook/Private/Windows");
        }
        else if (Target.Platform == UnrealTargetPlatform.IOS)
        {
            //Facebook API
            PublicDependencyModuleNames.AddRange(new string[] { "Facebook" });

            //Include
            PublicIncludePaths.Add("OnlineSubsystemFacebook/Private/IOS");
        }
        else if (Target.Platform == UnrealTargetPlatform.Android)
        {
            //Include
            PublicIncludePaths.Add("OnlineSubsystemFacebook/Private/Android");
            PrivateIncludePathModuleNames.AddRange(new string[] { "Settings", "Launch" });
        }

        System.Console.WriteLine("");

    }
}
