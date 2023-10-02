// Snake Game, Copyright moonabyss. Al Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SnakeGame/Core/Types.h"

#include "SG_Pawn.generated.h"

class UCameraComponent;

UCLASS()
class SNAKEGAME_API ASG_Pawn : public APawn
{
    GENERATED_BODY()

public:
    ASG_Pawn();

public:
    /**
     * Updates pawn height fitting grid in viewport
     * @param InDim  grid dimensions
     * @param InCellSize  world size of the cell
     * @param InGridOrigin  world transformation of the grid
     */
    void UpdateLocation(const SnakeGame::Dim& InDim, int32 InCellSize, const FTransform& InGridOrigin);

protected:
    UPROPERTY(VisibleAnywhere)
    USceneComponent* Origin;

    UPROPERTY(VisibleAnywhere)
    UCameraComponent* Camera;

private:
    SnakeGame::Dim Dim;
    int32 CellSize;
    FTransform GridOrigin;
    FDelegateHandle OnResizeHandle;

    void OnViewportResized(FViewport* Viewport, uint32 Val);
};
