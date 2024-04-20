// Snake Game, Copyright moonabyss. All Rights Reserved.

#if WITH_AUTOMATION_TESTS

#include "Components/Button.h"
#include "Components/ComboBoxString.h"
#include "Components/TextBlock.h"
#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "SnakeGame/Tests/Utils/TestUtils.h"
#include "SnakeGame/UI/SG_GameOverWidget.h"
#include "SnakeGame/UI/SG_GameplayWidget.h"
#include "SnakeGame/UI/SG_StartGameWidget.h"

BEGIN_DEFINE_SPEC(FSnakeUI, "Snake", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)
UWorld* World;
END_DEFINE_SPEC(FSnakeUI)

DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FGameOverWidgetVisibleLatentCommand, USG_GameOverWidget*, Widget);
bool FGameOverWidgetVisibleLatentCommand::Update()
{
    return Widget->GetVisibility() == ESlateVisibility::Visible;
}

void FSnakeUI::Define()
{
    using namespace Moonabyss::Test;

    Describe("UI",
        [this]()
        {
            It("AllMenuComponentsShouldExist",
                [this]()
                {
                    AutomationOpenMap("/Game/Maps/MenuLevel");
                    World = GetTestGameWorld();

                    auto* StartGameWidget = FindWidgetByClass<USG_StartGameWidget>();
                    TestTrueExpr(StartGameWidget != nullptr);

                    auto* StartGameButton = Cast<UButton>(FindWidgetByName(StartGameWidget, "StartGameButton"));
                    TestTrueExpr(StartGameButton != nullptr);

                    auto* CloseGameButton = Cast<UButton>(FindWidgetByName(StartGameWidget, "CloseGameButton"));
                    TestTrueExpr(CloseGameButton != nullptr);

                    auto* GameSpeedComboBox = Cast<UComboBoxString>(FindWidgetByName(StartGameWidget, "GameSpeedComboBox"));
                    TestTrueExpr(GameSpeedComboBox != nullptr);

                    auto* GridSizeComboBox = Cast<UComboBoxString>(FindWidgetByName(StartGameWidget, "GridSizeComboBox"));
                    TestTrueExpr(GridSizeComboBox != nullptr);
                });

            It("AllGameplayComponentsShouldExist",
                [this]()
                {
                    AutomationOpenMap("/Game/Maps/GameLevel");
                    World = GetTestGameWorld();

                    auto* GameplayWidget = FindWidgetByClass<USG_GameplayWidget>();
                    TestTrueExpr(GameplayWidget != nullptr);

                    auto* TimeText = Cast<UTextBlock>(FindWidgetByName(GameplayWidget, "TimeText"));
                    TestTrueExpr(TimeText != nullptr);

                    auto* ScoreText = Cast<UTextBlock>(FindWidgetByName(GameplayWidget, "ScoreText"));
                    TestTrueExpr(ScoreText != nullptr);

                    auto* RestartGameText = Cast<UTextBlock>(FindWidgetByName(GameplayWidget, "RestartGameText"));
                    TestTrueExpr(RestartGameText != nullptr);
                });

            It("AllGameOverComponentsShouldExist",
                [this]()
                {
                    AutomationOpenMap("/Game/Maps/GameLevel");
                    World = GetTestGameWorld();
                    auto* GameOverWidget = FindWidgetByClass<USG_GameOverWidget>();

                    TestTrueExpr(GameOverWidget != nullptr);
                    TestTrueExpr(GameOverWidget->GetVisibility() == ESlateVisibility::Collapsed);

                    ADD_LATENT_AUTOMATION_COMMAND(FGameOverWidgetVisibleLatentCommand(GameOverWidget));
                    ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand(
                        [this, GameOverWidget]()
                        {
                            auto* ScoreText = Cast<UTextBlock>(FindWidgetByName(GameOverWidget, "ScoreText"));
                            TestTrueExpr(ScoreText != nullptr);

                            auto* RestartGameText = Cast<UTextBlock>(FindWidgetByName(GameOverWidget, "RestartGameText"));
                            TestTrueExpr(RestartGameText != nullptr);

                            auto* BackToMenuButton = Cast<UButton>(FindWidgetByName(GameOverWidget, "BackToMenuButton"));
                            TestTrueExpr(BackToMenuButton != nullptr);
                            return true;
                        }));
                });
        });
}

#endif
