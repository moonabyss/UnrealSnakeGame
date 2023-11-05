// Snake Game, Copyright moonabyss. Al Rights Reserved.

#include "SnakeGame/UI/SG_MenuHUD.h"
#include "SnakeGame/UI/SG_StartGameWidget.h"

void ASG_MenuHUD::BeginPlay()
{
    Super::BeginPlay();

    StartGameWidget = CreateWidget<USG_StartGameWidget>(GetWorld(), StartGameWidgetClass);
    check(StartGameWidget);
    StartGameWidget->AddToViewport();
}
