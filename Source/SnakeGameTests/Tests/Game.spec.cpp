// Snake Game, Copyright moonabyss. All Rights Reserved.

#if WITH_AUTOMATION_TESTS

#include "SnakeGame/Core/Game.h"
#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "SnakeGame/Core/Grid.h"
#include "Tests/Utils/SnakeTestUtils.h"

using namespace SnakeGame;

BEGIN_DEFINE_SPEC(FSnakeGame, "Snake", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)
TUniquePtr<Game> CoreGame;
Settings GS;
END_DEFINE_SPEC(FSnakeGame)

void FSnakeGame::Define()
{
    Describe("Core.Game",
        [this]()
        {
            BeforeEach(
                [this]()
                {
                    GS.gridDims = Dim{10, 10};
                    GS.snake.startPosition = Grid::center(GS.gridDims.width, GS.gridDims.height);
                    GS.gameSpeed = 1.0f;
                    CoreGame = MakeUnique<Game>(GS);
                });

            It("GridShouldExists", [this]() { TestTrueExpr(CoreGame->grid().IsValid()); });
            It("SnakeShouldExists", [this]() { TestTrueExpr(CoreGame->snake().IsValid()); });
            It("FoodShouldExists", [this]() { TestTrueExpr(CoreGame->food().IsValid()); });

            It("GameCanBeOver",
                [this]()
                {
                    bool bGameOver{false};
                    CoreGame->subscribeOnGameplayEvent(
                        [&bGameOver](GameplayEvent Event)
                        {
                            if (Event == GameplayEvent::GameOver)
                            {
                                bGameOver = true;
                            }
                        });

                    const int32 Moves = FMath::RoundToInt(GS.gridDims.width / 2.0f) - 1;
                    for (int32 i = 0; i < Moves; ++i)
                    {
                        CoreGame->update(GS.gameSpeed, Input::Default);
                        TestTrueExpr(!bGameOver);
                    }

                    CoreGame->update(GS.gameSpeed, Input::Default);
                    TestTrueExpr(bGameOver);
                });
        });

    Describe("Core.Game",
        [this]()
        {
            It("FoodCanBeTaken",
                [this]()
                {
                    auto Randomizer = MakeShared<Test::MockPositionRandomizer>();
                    Randomizer->setPositions({
                        Position{7, 6},
                        Position{9, 6},
                        Position::Zero
                    });

                    GS.gridDims = Dim{10, 10};
                    GS.snake.startPosition = Grid::center(GS.gridDims.width, GS.gridDims.height);
                    GS.gameSpeed = 1.0f;
                    CoreGame = MakeUnique<Game>(GS, Randomizer);

                    uint32 Score = 0;
                    CoreGame->subscribeOnGameplayEvent(
                        [&Score](GameplayEvent Event)
                        {
                            if (Event == GameplayEvent::FoodTaken)
                            {
                                ++Score;
                            }
                        });

                    TestTrueExpr(CoreGame->score() == 0);
                    TestTrueExpr(Score == 0);

                    CoreGame->update(GS.gameSpeed, Input::Default);
                    TestTrueExpr(CoreGame->score() == 1);
                    TestTrueExpr(Score == 1);

                    CoreGame->update(GS.gameSpeed, Input::Default);
                    TestTrueExpr(CoreGame->score() == 1);
                    TestTrueExpr(Score == 1);

                    CoreGame->update(GS.gameSpeed, Input::Default);
                    TestTrueExpr(CoreGame->score() == 2);
                    TestTrueExpr(Score == 2);
                });
        });

    Describe("Core.Game", [this]() {  //
        It("SnakeShouldMoveCorrectlyNextToItsTail",
            [this]()
            {
                auto Randomizer = MakeShared<Test::MockPositionRandomizer>();
                Randomizer->setPositions({
                    Position{1, 1}
                });

                GS.gridDims = Dim{10, 10};
                GS.snake.defaultSize = 4;
                GS.snake.startPosition = Grid::center(GS.gridDims.width, GS.gridDims.height);
                GS.gameSpeed = 1.0f;
                CoreGame = MakeUnique<Game>(GS, Randomizer);

                bool bGameOver{false};
                CoreGame->subscribeOnGameplayEvent(
                    [&](GameplayEvent Event)
                    {
                        if (Event == GameplayEvent::GameOver)
                        {
                            bGameOver = true;
                        }
                    });

                CoreGame->update(GS.gameSpeed, {0, 1});   // move down
                CoreGame->update(GS.gameSpeed, {-1, 0});  // move left
                CoreGame->update(GS.gameSpeed, {0, -1});  // move up

                TestTrueExpr(!bGameOver);  // the snake shouldn't bite its tail
            });
    });
}

#endif
