// Snake Game, Copyright moonabyss. Al Rights Reserved.

using UnrealBuildTool;
using System.Linq;

public class SnakeGameTests : ModuleRules
{
    public SnakeGameTests(ReadOnlyTargetRules Target)
        : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG", "SnakeGame" });
        PublicIncludePaths.AddRange(new string[] { "SnakeGameTests" });

        if (Target.Configuration != UnrealTargetConfiguration.Shipping)
        {
            PublicDependencyModuleNames.Add("FunctionalTesting");
        }
    }
}
