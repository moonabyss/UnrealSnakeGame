// Snake Game, Copyright moonabyss. All Rights Reserved.

#if WITH_AUTOMATION_TESTS

#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "Misc/PathViews.h"
#include "SnakeGame/Framework/SG_GameMode.h"
#include "SnakeGame/Framework/SG_GameUserSettings.h"
#include "SnakeGame/Framework/SG_Pawn.h"
#include "SnakeGame/Tests/Utils/TestUtils.h"

BEGIN_DEFINE_SPEC(FSnakeFramework, "Snake", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)
UWorld* World;
USG_GameUserSettings* GameUserSettings;
END_DEFINE_SPEC(FSnakeFramework)

void FSnakeFramework::Define()
{
    using namespace Moonabyss::Test;

    Describe("Framework",
        [this]()
        {
            It("GameMapShouldExists",
                [this]()
                {
                    const TArray<FString> SnakeGameMaps = {"GameLevel", "MenuLevel"};
                    TArray<FString> AllProjectMaps;
                    IFileManager::Get().FindFilesRecursive(AllProjectMaps, *FPaths::ProjectContentDir(), TEXT("*.umap"), true, false);

                    for (const auto& SnakeGameMap : SnakeGameMaps)
                    {
                        const bool SnakeMapExists = AllProjectMaps.ContainsByPredicate(
                            [&](const FString& ProjectMap)
                            {
                                FStringView OutPath, OutName, OutExt;
                                FPathViews::Split(FStringView(ProjectMap), OutPath, OutName, OutExt);
                                return SnakeGameMap.Equals(FString(OutName));
                            });
                        TestTrue(FString::Printf(TEXT("Map exists: %s"), *SnakeGameMap), SnakeMapExists);
                    }
                });
        });

    Describe("Framework",
        [this]()
        {
            BeforeEach(
                [this]()
                {
                    AutomationOpenMap("/Game/Maps/GameLevel");
                    World = GetTestGameWorld();
                });

            It("ClassesShouldBeSetupCorrectly",
                [this]()
                {
                    TestNotNull("Snake game mode set up", Cast<ASG_GameMode>(World->GetAuthGameMode()));
                    TestNotNull("Snake pawn set up", Cast<ASG_Pawn>(World->GetFirstPlayerController()->GetPawn()));
                });
            xIt("PawnLocationShouldBeAdjustedCorrectly", [this]() { unimplemented(); });
        });

    Describe("Framework.GameUserSettings",
        [this]()
        {
            BeforeEach([this]() { GameUserSettings = NewObject<USG_GameUserSettings>(); });

            It("SpeedOptionsShouldExist",
                [this]()
                {
                    const TArray<FString> TestOptions{"Worm", "Snake", "Python"};
                    const auto SpeedOptions = GameUserSettings->GameSpeedOptions();

                    TestTrueExpr(TestOptions.Num() == SpeedOptions.Num());

                    for (const auto& Option : TestOptions)
                    {
                        TestTrueExpr(SpeedOptions.Find(Option) != INDEX_NONE);
                    }
                });

            It("SpeedElemCouldBeFindByName",
                [this]()
                {
                    const TArray<TTuple<FString, EGameSpeed>> TestData{
                        {"Worm",   EGameSpeed::Worm  },
                        {"Snake",  EGameSpeed::Snake },
                        {"Python", EGameSpeed::Python},
                    };

                    for (const auto& [Name, SpeedType] : TestData)
                    {
                        TestTrueExpr(SpeedType == GameUserSettings->GameSpeedByName(Name));
                    }
                });

            It("SpeedElemShouldBeDefaultIfNameDoesNotExist", [this]() { TestTrueExpr(EGameSpeed::Snake == GameUserSettings->GameSpeedByName("xxxxx")); });

            It("SpeedSetingsCanBeSaved",
                [this]()
                {
                    const TArray<TTuple<FString, EGameSpeed, float>> TestData{
                        {"Worm",   EGameSpeed::Worm,   0.2f  },
                        {"Snake",  EGameSpeed::Snake,  0.1f  },
                        {"Python", EGameSpeed::Python, 0.075f},
                    };

                    for (const auto& [Name, SpeedType, Speed] : TestData)
                    {
                        GameUserSettings->SaveSnakeSettings(SpeedType, EGridSize::Size_30x10);
                        TestTrueExpr(GameUserSettings->CurrentGameSpeedOption().Equals(Name));
                        TestTrueExpr(GameUserSettings->GameSpeed() == Speed);
                    }
                });

            It("GridSizeOptionsShouldExist",
                [this]()
                {
                    const TArray<FString> TestOptions{"30x10", "50x15", "80x20"};
                    const auto GridOptions = GameUserSettings->GridSizesOptions();

                    TestTrueExpr(TestOptions.Num() == GridOptions.Num());

                    for (const auto& Option : TestOptions)
                    {
                        TestTrueExpr(GridOptions.Find(Option) != INDEX_NONE);
                    }
                });

            It("GridSizeElemCouldBeFindByName",
                [this]()
                {
                    const TArray<TTuple<FString, EGridSize>> TestData{
                        {"30x10", EGridSize::Size_30x10},
                        {"50x15", EGridSize::Size_50x15},
                        {"80x20", EGridSize::Size_80x20},
                    };

                    for (const auto& [Name, GridSizeType] : TestData)
                    {
                        TestTrueExpr(GridSizeType == GameUserSettings->GridSizeByName(Name));
                    }
                });

            It("GridSizeElemShouldBeDefaultIfNameDoesNotExist", [this]() { TestTrueExpr(EGridSize::Size_50x15 == GameUserSettings->GridSizeByName("xxxxx")); });

            It("GridSizeSetingsCanBeSaved",
                [this]()
                {
                    const TArray<TTuple<FString, EGridSize, SnakeGame::Dim>> TestData{
                        {"30x10", EGridSize::Size_30x10, SnakeGame::Dim{30, 10}},
                        {"50x15", EGridSize::Size_50x15, SnakeGame::Dim{50, 15}},
                        {"80x20", EGridSize::Size_80x20, SnakeGame::Dim{80, 20}},
                    };

                    for (const auto& [Name, GridSizeType, GridSize] : TestData)
                    {
                        GameUserSettings->SaveSnakeSettings(EGameSpeed::Snake, GridSizeType);
                        TestTrueExpr(GameUserSettings->CurrentGridSizeOption().Equals(Name));
                        TestTrueExpr(GameUserSettings->GridSize() == GridSize);
                    }
                });
        });
}

#endif
