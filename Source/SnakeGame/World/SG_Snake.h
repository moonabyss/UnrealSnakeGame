// Snake Game, Copyright moonabyss. Al Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SnakeGame/Core/Snake.h"
#include "SnakeGame/World/SG_WorldTypes.h"

#include "SG_Snake.generated.h"

class ASG_SnakeLink;

UCLASS()
class SNAKEGAME_API ASG_Snake : public AActor
{
    GENERATED_BODY()

public:
    ASG_Snake();
    virtual void Tick(float DeltaTime) override;

    /**
     * Set core model to be observed by the Snake world actor
     * @param Snake  model object
     * @param CellSize  world size of the cell
     * @param Dims  dimensions of the grid
     */
    void SetModel(const TSharedPtr<SnakeGame::Snake>& InSnake, uint32 InCellSize, const SnakeGame::Dim& InDims);

    void UpdateColors(const FSnakeColors& Colors);

protected:
    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<ASG_SnakeLink> SnakeHeadClass;

    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<ASG_SnakeLink> SnakeLinkClass;

private:
    TWeakPtr<SnakeGame::Snake> Snake;
    uint32 CellSize;
    SnakeGame::Dim Dims;

    UPROPERTY()
    TArray<ASG_SnakeLink*> SnakeLinks;

    UPROPERTY()
    FLinearColor SnakeLinkColor{FLinearColor::Black};
};
