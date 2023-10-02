// Snake Game, Copyright moonabyss. Al Rights Reserved.

#include "SnakeGame/World/SG_Grid.h"
#include "Components/LineBatchComponent.h"
#include "Components/StaticMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "SnakeGame/Core/Grid.h"

DEFINE_LOG_CATEGORY_STATIC(LogWorldGrid, All, All)

ASG_Grid::ASG_Grid()
{
    PrimaryActorTick.bCanEverTick = false;

    Origin = CreateDefaultSubobject<USceneComponent>("Origin");
    check(Origin);
    SetRootComponent(Origin);

    GridMesh = CreateDefaultSubobject<UStaticMeshComponent>("GridMesh");
    check(GridMesh);
    GridMesh->SetupAttachment(Origin);
}

void ASG_Grid::BeginPlay()
{
    Super::BeginPlay();
}

void ASG_Grid::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ASG_Grid::SetModel(const TSharedPtr<SnakeGame::Grid>& Grid, uint32 InCellSize)
{
    if (!Grid)
    {
        UE_LOG(LogWorldGrid, Fatal, TEXT("Grid is null, game aborted!"));
    }
    GridDim = Grid->dim();
    CellSize = InCellSize;
    WorldWidth = GridDim.width * CellSize;
    WorldHeight = GridDim.height * CellSize;

    // scale mesh
    check(GridMesh->GetStaticMesh());
    const FBox Box = GridMesh->GetStaticMesh()->GetBoundingBox();
    const auto Size = Box.GetSize();

    check(Size.X);
    check(Size.Y);
    GridMesh->SetRelativeScale3D(FVector(WorldHeight / Size.X, WorldWidth / Size.Y, 1.0));
    GridMesh->SetWorldLocation(0.5 * FVector(WorldHeight, WorldWidth, -Size.Z));

    // setup material
    GridMaterial = GridMesh->CreateAndSetMaterialInstanceDynamic(0);
    if (GridMaterial)
    {
        GridMaterial->SetVectorParameterValue("Division", FVector(GridDim.height, GridDim.width, 0.0));
    }
}

void ASG_Grid::UpdateColors(const FSnakeColors& Colors)
{
    if (GridMaterial)
    {
        GridMaterial->SetVectorParameterValue("BackgroundColor", Colors.GridBackgroundColor);
        GridMaterial->SetVectorParameterValue("WallColor", Colors.GridWallColor);
        GridMaterial->SetVectorParameterValue("LineColor", Colors.GridLineColor);
    }
}

void ASG_Grid::DrawGrid()
{
    if (!GetWorld() || !GetWorld()->LineBatcher) return;

    for (uint32 i = 0; i < GridDim.height + 1; ++i)
    {
        const FVector StartLocation = GetActorLocation() + GetActorForwardVector() * CellSize * i;
        const FVector EndLocation = StartLocation + GetActorRightVector() * WorldWidth;
        GetWorld()->LineBatcher->DrawLine(StartLocation, EndLocation, FLinearColor::Red, 1, 2.0f);
    }

    for (uint32 i = 0; i < GridDim.width + 1; ++i)
    {
        const FVector StartLocation = GetActorLocation() + GetActorRightVector() * CellSize * i;
        const FVector EndLocation = StartLocation + GetActorForwardVector() * WorldHeight;
        GetWorld()->LineBatcher->DrawLine(StartLocation, EndLocation, FLinearColor::Red, 1, 2.0f);
    }
}
