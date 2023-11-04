// Snake Game, Copyright moonabyss. Al Rights Reserved.

#include "SnakeGame/UI/SG_GameplayWidget.h"
#include "Components/TextBlock.h"
#include "SnakeGame/World/SG_WorldUtils.h"

void USG_GameplayWidget::SetGameTime(float Seconds)
{
    if (TimeText)
    {
        TimeText->SetText(SnakeGame::WorldUtils::FormatSeconds(Seconds));
    }
}

void USG_GameplayWidget::SetScore(uint32 Score)
{
    if (ScoreText)
    {
        ScoreText->SetText(SnakeGame::WorldUtils::FormatScore(Score));
    }
}

void USG_GameplayWidget::SetResetGameKeyName(const FString& ResetGameKeyName)
{
    if (RestartGameText)
    {
        const FString ResetGameInfo = FString::Printf(TEXT("press <%s> to restart"), *ResetGameKeyName.ToLower());
        RestartGameText->SetText(FText::FromString(ResetGameInfo));
    }
}
