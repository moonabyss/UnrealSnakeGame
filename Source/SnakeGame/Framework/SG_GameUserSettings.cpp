// Snake Game, Copyright moonabyss. Al Rights Reserved.

#include "SnakeGame/Framework/SG_GameUserSettings.h"

USG_GameUserSettings::USG_GameUserSettings()
{
    check(GameSpeeds.Num() == StaticEnum<EGameSpeed>()->NumEnums() - 1);
    check(GridSizes.Num() == StaticEnum<EGridSize>()->NumEnums() - 1);
}

USG_GameUserSettings* USG_GameUserSettings::Get()
{
    return GEngine ? Cast<USG_GameUserSettings>(GEngine->GetGameUserSettings()) : nullptr;
}

void USG_GameUserSettings::SaveSnakeSettings(EGameSpeed GameSpeed, EGridSize GridSize)
{
    //@todo: check if enum elems exist in TMap
    CurrentGameSpeed = GameSpeeds[GameSpeed];
    CurrentGridSize = GridSizes[GridSize];
}
