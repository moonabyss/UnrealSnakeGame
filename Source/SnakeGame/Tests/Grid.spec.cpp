// Snake Game, Copyright moonabyss. All Rights Reserved.

#if WITH_AUTOMATION_TESTS

#include "SnakeGame/Core/Grid.h"
#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"

DEFINE_SPEC(FSnakeGrid, "Snake", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)

void FSnakeGrid::Define()
{
    using namespace SnakeGame;

    Describe("CoreGrid",
        [this]()
        {
            It("DimsShouldIncludeWalls",
                [this]()
                {
                    const Grid grid(Dim{20, 10});
                    TestTrueExpr(grid.dim().width == 22);
                    TestTrueExpr(grid.dim().height == 12);
                });
        });
}

#endif
