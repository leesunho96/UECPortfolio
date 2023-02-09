using UnrealBuildTool;

public class Weapon : ModuleRules
{
	public Weapon(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.Add(ModuleDirectory);

        PublicDependencyModuleNames.Add("Core");

        PrivateDependencyModuleNames.Add("U2112_04");

        PrivateDependencyModuleNames.Add("CoreUObject");
        PrivateDependencyModuleNames.Add("Engine");
        PrivateDependencyModuleNames.Add("Slate");
        PrivateDependencyModuleNames.Add("SlateCore");
        PrivateDependencyModuleNames.Add("Projects");
        PrivateDependencyModuleNames.Add("EditorStyle");
        PrivateDependencyModuleNames.Add("UnrealEd");
        PrivateDependencyModuleNames.Add("InputCore");
    }
}
