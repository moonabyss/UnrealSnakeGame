// Snake Game, Copyright moonabyss. Al Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class SnakeGameEditorTarget : TargetRules
{
    public bool UnoptimizedCode = false;

    public SnakeGameEditorTarget(TargetInfo Target)
        : base(Target)
    {
        if (UnoptimizedCode)
        {
            ProjectDefinitions.Add("UNOPTIMIZED_CODE");
        }

        Type = TargetType.Editor;
        DefaultBuildSettings = BuildSettingsVersion.V4;
        IncludeOrderVersion = EngineIncludeOrderVersion.Latest;

        ExtraModuleNames.AddRange(new string[] { "SnakeGame", "SnakeGameTests" });
    }
}
