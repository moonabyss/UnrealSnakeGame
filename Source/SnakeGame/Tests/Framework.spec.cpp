// Snake Game, Copyright moonabyss. All Rights Reserved.

#if WITH_AUTOMATION_TESTS

#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "Misc/PathViews.h"
#include "SnakeGame/Framework/SG_GameMode.h"
#include "SnakeGame/Framework/SG_Pawn.h"
#include "SnakeGame/Tests/Utils/TestUtils.h"

BEGIN_DEFINE_SPEC(FSnakeFramework, "Snake", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)
UWorld* World;
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
                    const TArray<FString> SnakeGameMaps = {"GameLevel"};
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
                    AutomationOpenMap("GameLevel");
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
}

#endif
