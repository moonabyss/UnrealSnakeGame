// Snake Game, Copyright moonabyss. Al Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/GameModeBase.h"
#include "InputActionValue.h"
#include "SnakeGame/Core/Game.h"

#include "SG_GameMode.generated.h"

class AExponentialHeightFog;
class ASG_Food;
class ASG_Grid;
class ASG_HUD;
class ASG_Snake;
class UInputAction;
class UInputMappingContext;

UCLASS()
class SNAKEGAME_API ASG_GameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    ASG_GameMode();

    virtual void StartPlay() override;
    virtual void Tick(float DeltaSeconds) override;

protected:
    UPROPERTY(Category = "Settings", EditDefaultsOnly)
    bool bOverrideUserSettings{false};

    UPROPERTY(Category = "Settings", EditDefaultsOnly, meta = (ClampMin = "10", ClampMax = "100", EditCondition = "bOverrideUserSettings", EditConditionHides))
    FUintPoint GridDims{10, 10};

    UPROPERTY(Category = "Settings", EditDefaultsOnly, meta = (ClampMin = "0.01", ClampMax = "10", EditCondition = "bOverrideUserSettings", EditConditionHides))
    float GameSpeed{1.0f};

    UPROPERTY(Category = "Settings", EditDefaultsOnly, meta = (ClampMin = "10", ClampMax = "100", EditCondition = "bOverrideUserSettings", EditConditionHides))
    uint32 CellSize{10};

    UPROPERTY(Category = "Settings", EditDefaultsOnly, meta = (ClampMin = "4", ClampMax = "10", EditCondition = "bOverrideUserSettings", EditConditionHides))
    uint32 SnakeDefaultSize{5};

    UPROPERTY(Category = "Design", EditDefaultsOnly)
    TSubclassOf<ASG_Grid> GridVisualClass;

    UPROPERTY(Category = "Design", EditDefaultsOnly)
    TSubclassOf<ASG_Snake> SnakeVisualClass;

    UPROPERTY(Category = "Design", EditDefaultsOnly)
    TSubclassOf<ASG_Food> FoodVisualClass;

    UPROPERTY(Category = "Design", EditDefaultsOnly)
    TObjectPtr<UDataTable> ColorsTable;

    UPROPERTY(Category = "SnakeInput", EditDefaultsOnly)
    TObjectPtr<UInputAction> MoveForwardInputAction;

    UPROPERTY(Category = "SnakeInput", EditDefaultsOnly)
    TObjectPtr<UInputAction> MoveRightInputAction;

    UPROPERTY(Category = "SnakeInput", EditDefaultsOnly)
    TObjectPtr<UInputAction> ResetGameInputAction;

    UPROPERTY(Category = "SnakeInput", EditDefaultsOnly)
    TObjectPtr<UInputMappingContext> InputMapping;

private:
    UPROPERTY()
    TObjectPtr<ASG_Grid> GridVisual;

    UPROPERTY()
    TObjectPtr<ASG_Snake> SnakeVisual;

    UPROPERTY()
    TObjectPtr<ASG_Food> FoodVisual;

    UPROPERTY()
    TObjectPtr<AExponentialHeightFog> Fog;

    UPROPERTY()
    TObjectPtr<ASG_HUD> HUD;

    UFUNCTION(Category = "Console command", Exec)
    void NextColor();

    TSharedPtr<SnakeGame::Game> Game;
    uint32 ColorTableIndex{0};
    SnakeGame::Input SnakeInput{SnakeGame::Input::Default};
    SnakeGame::Settings MakeSettings() const;

    void FindFog();

    /**
     * Updates Grid and ExponentialFog colours
     * according to the ColorsTable property
     */
    void UpdateColors();

    void SetupInput();
    void OnMoveForward(const FInputActionValue& Value);
    void OnMoveRight(const FInputActionValue& Value);
    void OnGameReset(const FInputActionValue& Value);

    void SubscribeOnGameEvents();
};
