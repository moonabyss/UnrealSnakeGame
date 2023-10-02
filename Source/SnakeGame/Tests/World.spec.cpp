// Snake Game, Copyright moonabyss. All Rights Reserved.

#if WITH_AUTOMATION_TESTS

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/AutomationTest.h"
#include "SnakeGame/Core/Grid.h"
#include "SnakeGame/Tests/Utils/TestUtils.h"
#include "SnakeGame/World/SG_Grid.h"
#include "SnakeGame/World/SG_WorldTypes.h"

BEGIN_DEFINE_SPEC(FSnakeWorld, "Snake", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)
UWorld* World;
SnakeGame::Dim Dims;
uint32 CellSize;
TSharedPtr<SnakeGame::Grid> ModelGrid;
UStaticMeshComponent* GridStaticMesh;
ASG_Grid* VisualGrid;
END_DEFINE_SPEC(FSnakeWorld)

void FSnakeWorld::Define()
{
    using namespace Moonabyss::Test;

    Describe("WorldGrid",
        [this]()
        {
            BeforeEach(
                [this]()
                {
                    AutomationOpenMap("TestEmptyLevel");
                    World = GetTestGameWorld();

                    constexpr char* GridBPName = "Blueprint'/Game/World/BP_SnakeGrid.BP_SnakeGrid'";

                    Dims = SnakeGame::Dim{10, 10};
                    CellSize = 20;
                    ModelGrid = MakeShared<SnakeGame::Grid>(Dims);

                    const FTransform Origin = FTransform::Identity;
                    VisualGrid = CreateBlueprintDeferred<ASG_Grid>(World, GridBPName, Origin);
                    VisualGrid->SetModel(ModelGrid, CellSize);
                    VisualGrid->FinishSpawning(Origin);

                    auto* Comp = VisualGrid->GetComponentByClass(UStaticMeshComponent::StaticClass());
                    GridStaticMesh = Cast<UStaticMeshComponent>(Comp);
                });

            It("StaticGridShouldHaveCorrectTransform",
                [this]()
                {
                    const FBox Box = GridStaticMesh->GetStaticMesh()->GetBoundingBox();
                    const auto Size = Box.GetSize();

                    const auto WorldWidth = ModelGrid->dim().width * CellSize;
                    const auto WorldHeight = ModelGrid->dim().height * CellSize;

                    TestTrueExpr(GridStaticMesh->GetRelativeLocation().Equals(0.5 * FVector(WorldHeight, WorldWidth, -Size.Z)));
                    TestTrueExpr(GridStaticMesh->GetRelativeScale3D().Equals(FVector(WorldHeight / Size.X, WorldWidth / Size.Y, 1.0)));
                });
            It("ColorsShouldBeSetupCorrectly",
                [this]()
                {
                    FSnakeColors Colors;
                    Colors.GridBackgroundColor = FLinearColor::Green;
                    Colors.GridWallColor = FLinearColor::Red;
                    Colors.GridLineColor = FLinearColor::Yellow;
                    VisualGrid->UpdateColors(Colors);

                    auto* Material = GridStaticMesh->GetMaterial(0);
                    FLinearColor ColorToCheck;

                    Material->GetVectorParameterValue(FName("BackgroundColor"), ColorToCheck);
                    TestTrueExpr(ColorToCheck.Equals(Colors.GridBackgroundColor));

                    Material->GetVectorParameterValue(FName("WallColor"), ColorToCheck);
                    TestTrueExpr(ColorToCheck.Equals(Colors.GridWallColor));

                    Material->GetVectorParameterValue(FName("LineColor"), ColorToCheck);
                    TestTrueExpr(ColorToCheck.Equals(Colors.GridLineColor));
                });
        });

    Describe("WorldGrid",
        [this]()
        {
            BeforeEach(
                [this]()
                {
                    AutomationOpenMap("GameLevel");
                    World = GetTestGameWorld();
                });

            It("OnlyOneValidGridActorShouldExists",
                [this]()
                {
                    TArray<AActor*> Grids;
                    UGameplayStatics::GetAllActorsOfClass(World, ASG_Grid::StaticClass(), Grids);
                    TestTrueExpr(Grids.Num() == 1);
                    TestNotNull("Grid actor exists", Grids[0]);
                });
        });
}
#endif
