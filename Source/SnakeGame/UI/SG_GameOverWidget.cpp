// Snake Game, Copyright moonabyss. Al Rights Reserved.

#include "SnakeGame/UI/SG_GameOverWidget.h"
#include "Components/TextBlock.h"
#include "SnakeGame/World/SG_WorldUtils.h"

void USG_GameOverWidget::SetScore(uint32 Score)
{
    if (ScoreText)
    {
        ScoreText->SetText(SnakeGame::WorldUtils::FormatScore(Score));
    }
}

void USG_GameOverWidget::SetResetGameKeyName(const FString& ResetGameKeyName)
{
    if (RestartGameText)
    {
        const FString ResetGameInfo = FString::Printf(TEXT("press <%s> to restart"), *ResetGameKeyName.ToLower());
        RestartGameText->SetText(FText::FromString(ResetGameInfo));
    }
}
