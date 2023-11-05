// Snake Game, Copyright moonabyss. Al Rights Reserved.

#include "SnakeGame/Framework/SG_MenuGameMode.h"
#include "SnakeGame/World/SG_WorldUtils.h"

void ASG_MenuGameMode::StartPlay()
{
    Super::StartPlay();

    SnakeGame::WorldUtils::SetUIInput(GetWorld(), true);
}
