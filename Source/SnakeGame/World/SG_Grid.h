// Snake Game, Copyright moonabyss. Al Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SnakeGame/Core/Types.h"
#include "SnakeGame/World/SG_WorldTypes.h"

#include "SG_Grid.generated.h"

namespace SnakeGame
{
class Grid;
}

UCLASS()
class SNAKEGAME_API ASG_Grid : public AActor
{
    GENERATED_BODY()

public:
    ASG_Grid();
    virtual void Tick(float DeltaTime) override;

protected:
    virtual void BeginPlay() override;

public:
    /**
     * Set core model to be observed by the grid world actor
     * @param Grid  model object
     * @param InCellSize  world size of the cell
     */
    void SetModel(const TSharedPtr<SnakeGame::Grid>& Grid, uint32 InCellSize);

    void UpdateColors(const FSnakeColors& Colors);

protected:
    UPROPERTY(VisibleAnywhere)
    USceneComponent* Origin;

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* GridMesh;

private:
    UPROPERTY()
    UMaterialInstanceDynamic* GridMaterial;

    SnakeGame::Dim GridDim;
    uint32 CellSize;
    uint32 WorldWidth;
    uint32 WorldHeight;

    void DrawGrid();
};
