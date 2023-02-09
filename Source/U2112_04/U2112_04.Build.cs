using UnrealBuildTool;

public class U2112_04 : ModuleRules
{
	public U2112_04(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.Add(ModuleDirectory);
	
		PublicDependencyModuleNames.Add("Core");
        PublicDependencyModuleNames.Add("CoreUObject");
        PublicDependencyModuleNames.Add("Engine");
        PublicDependencyModuleNames.Add("InputCore");
        PublicDependencyModuleNames.Add("Niagara");
        PublicDependencyModuleNames.Add("AIModule");
        PublicDependencyModuleNames.Add("GameplayTasks");
    }
}
