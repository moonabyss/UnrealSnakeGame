// Snake Game, Copyright moonabyss. Al Rights Reserved.

using UnrealBuildTool;
using System.Linq;

public class SnakeGame : ModuleRules
{
    public SnakeGame(ReadOnlyTargetRules Target)
        : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG", "EnhancedInput", "Niagara", "SlateCore" });
    }
}
