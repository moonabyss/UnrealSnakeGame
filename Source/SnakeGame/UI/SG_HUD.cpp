// Snake Game, Copyright moonabyss. Al Rights Reserved.

#include "SnakeGame/UI/SG_HUD.h"
#include "SnakeGame/Core/Game.h"
#include "SnakeGame/UI/SG_GameOverWidget.h"
#include "SnakeGame/UI/SG_GameplayWidget.h"

void ASG_HUD::BeginPlay()
{
    Super::BeginPlay();

    GameplayWidget = CreateWidget<USG_GameplayWidget>(GetWorld(), GameplayWidgetClass);
    check(GameplayWidget);
    GameWidgets.Add(EUIGameState::GameInProgress, GameplayWidget);

    GameOverWidget = CreateWidget<USG_GameOverWidget>(GetWorld(), GameOverWidgetClass);
    check(GameOverWidget);
    GameWidgets.Add(EUIGameState::GameOver, GameOverWidget);

    for (auto& [UIState, GameWidget] : GameWidgets)
    {
        if (GameWidget)
        {
            GameWidget->AddToViewport();
            GameWidget->SetVisibility(ESlateVisibility::Collapsed);
        }
    }
}

void ASG_HUD::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    if (Game.IsValid() && GameState == EUIGameState::GameInProgress)
    {
        GameplayWidget->SetGameTime(Game.Pin()->gameTime());
    }
}

void ASG_HUD::SetModel(const TSharedPtr<SnakeGame::Game>& InGame)
{
    if (!InGame) return;

    using namespace SnakeGame;

    Game = InGame;

    SetUIMatchState(EUIGameState::GameInProgress);
    GameplayWidget->SetScore(InGame->score());
    GameOverWidget->SetScore(InGame->score());

    InGame->subscribeOnGameplayEvent(
        [&](GameplayEvent Event)
        {
            switch (Event)
            {
                case GameplayEvent::FoodTaken:  //
                    GameplayWidget->SetScore(InGame->score());
                    break;

                case SnakeGame::GameplayEvent::GameCompleted: [[fallthrough]];
                case SnakeGame::GameplayEvent::GameOver:  //
                    GameOverWidget->SetScore(InGame->score());
                    SetUIMatchState(EUIGameState::GameOver);
                    break;
            }
        });
}

void ASG_HUD::SetInputKeyNames(const FString& ResetGameKeyName)
{
    GameplayWidget->SetResetGameKeyName(ResetGameKeyName);
    GameOverWidget->SetResetGameKeyName(ResetGameKeyName);
}

void ASG_HUD::SetUIMatchState(EUIGameState InMatchState)
{
    if (CurrentWidget)
    {
        CurrentWidget->SetVisibility(ESlateVisibility::Collapsed);
    }

    if (GameWidgets.Contains(InMatchState))
    {
        CurrentWidget = GameWidgets[InMatchState];
        CurrentWidget->SetVisibility(ESlateVisibility::Visible);
    }

    GameState = InMatchState;
}