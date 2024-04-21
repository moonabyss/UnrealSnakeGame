// Snake Game, Copyright moonabyss. All Rights Reserved.

#if WITH_AUTOMATION_TESTS

#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"

#include "SnakeGame/Core/Grid.h"
#include "SnakeGame/Core/Utils.h"

DEFINE_SPEC(FPositionRandomizer, "Snake", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::StressFilter | EAutomationTestFlags::HighPriority)

void FPositionRandomizer::Define()
{
    Describe("PositionRandomizer",
        [this]()
        {
            It("FreeCellShouldBeFound",
                [this]()
                {
                    using namespace SnakeGame;

                    const Dim Dimensions{10, 10};
                    const auto Randomizer = MakeShared<PositionRandomizer>();
                    auto TestGrid = MakeShared<Grid>(Dimensions, Randomizer);

                    Position Pos;

                    for (int32 i = 0; i < 1000; ++i)
                    {
                        const bool Result = TestGrid->randomEmptyPosition(Pos);
                        TestTrueExpr(Result);
                        TestTrueExpr(Pos.x >= 1 && Pos.x <= Dimensions.width);
                        TestTrueExpr(Pos.y >= 1 && Pos.y <= Dimensions.height);
                    }
                });
        });
}

#endif
