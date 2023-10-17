// Snake Game, Copyright moonabyss. All Rights Reserved.

#if WITH_AUTOMATION_TESTS

#include "SnakeGame/Core/Food.h"
#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "SnakeGame/Core/Types.h"

DEFINE_SPEC(FSnakeFood, "Snake", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)

void FSnakeFood::Define()
{
    using namespace SnakeGame;

    Describe("Core.Food",
        [this]()
        {
            It("PositionCanBeUpdated",
                [this]()
                {
                    const Position Pos = Position(45, 67);
                    Food CoreFood;
                    CoreFood.setPosition(Pos);
                    TestTrueExpr(CoreFood.position() == Pos);
                });
        });
}

#endif
