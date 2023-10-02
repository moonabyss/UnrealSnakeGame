// Snake Game, Copyright moonabyss. Al Rights Reserved.

#include "SnakeGame/Framework/SG_GameMode.h"
#include "Components/ExponentialHeightFogComponent.h"
#include "Engine/ExponentialHeightFog.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "SnakeGame/Core/Grid.h"
#include "SnakeGame/Core/Types.h"
#include "SnakeGame/Framework/SG_Pawn.h"
#include "SnakeGame/World/SG_Grid.h"
#include "SnakeGame/World/SG_Snake.h"
#include "SnakeGame/World/SG_WorldTypes.h"

ASG_GameMode::ASG_GameMode()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ASG_GameMode::StartPlay()
{
    Super::StartPlay();

    // init core game
    Game = MakeUnique<SnakeGame::Game>(MakeSettings());
    check(Game.IsValid());

    // init world grid
    const FTransform GridOrigin = FTransform::Identity;
    check(GetWorld());
    check(GridVisualClass);
    GridVisual = GetWorld()->SpawnActorDeferred<ASG_Grid>(GridVisualClass, GridOrigin);
    check(GridVisual);
    GridVisual->SetModel(Game->grid(), CellSize);
    GridVisual->FinishSpawning(GridOrigin);

    // init world snake
    check(SnakeVisualClass) SnakeVisual = GetWorld()->SpawnActorDeferred<ASG_Snake>(SnakeVisualClass, GridOrigin);
    check(SnakeVisual);
    SnakeVisual->SetModel(Game->snake(), CellSize, Game->grid()->dim());
    SnakeVisual->FinishSpawning(GridOrigin);

    // set pawn location fitting grid in viewport
    const auto* PC = GetWorld()->GetFirstPlayerController();
    check(PC);
    auto* Pawn = Cast<ASG_Pawn>(PC->GetPawn());
    check(Pawn);
    check(Game->grid().IsValid());
    Pawn->UpdateLocation(Game->grid()->dim(), CellSize, GridOrigin);

    //
    FindFog();

    // update colors
    check(ColorsTable);
    const auto RowsCount = ColorsTable->GetRowNames().Num();
    check(RowsCount > 0);
    ColorTableIndex = FMath::RandRange(0, RowsCount - 1);
    UpdateColors();

    //
    SetupInput();
}

void ASG_GameMode::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    if (Game.IsValid())
    {
        Game->update(DeltaSeconds, SnakeInput);
    }
}

void ASG_GameMode::FindFog()
{
    TArray<AActor*> Fogs;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AExponentialHeightFog::StaticClass(), Fogs);
    if (Fogs.Num() == 1)
    {
        Fog = Cast<AExponentialHeightFog>(Fogs[0]);
    }
}

void ASG_GameMode::UpdateColors()
{
    const auto RowName = ColorsTable->GetRowNames()[ColorTableIndex];
    const auto* ColorSet = ColorsTable->FindRow<FSnakeColors>(RowName, {});
    if (ColorSet)
    {
        // update grid
        GridVisual->UpdateColors(*ColorSet);

        // update snake
        SnakeVisual->UpdateColors(*ColorSet);

        // update scene ambient color via fog
        if (Fog && Fog->GetComponent())
        {
            Fog->GetComponent()->SkyAtmosphereAmbientContributionColorScale = ColorSet->SkyAtmosphereColor;
            Fog->MarkComponentsRenderStateDirty();
        }
    }
}

void ASG_GameMode::NextColor()
{
    if (ColorsTable)
    {
        ColorTableIndex = (ColorTableIndex + 1) % ColorsTable->GetRowNames().Num();
        UpdateColors();
    }
}

void ASG_GameMode::SetupInput()
{
    if (!GetWorld()) return;

    if (auto* PC = Cast<APlayerController>(GetWorld()->GetFirstPlayerController()))
    {
        if (auto* InputSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
        {
            InputSystem->AddMappingContext(InputMapping, 0);
        }

        auto* Input = Cast<UEnhancedInputComponent>(PC->InputComponent);
        check(Input);
        Input->BindAction(MoveForwardInputAction, ETriggerEvent::Triggered, this, &ThisClass::OnMoveForward);
        Input->BindAction(MoveRightInputAction, ETriggerEvent::Triggered, this, &ThisClass::OnMoveRight);
        Input->BindAction(ResetGameInputAction, ETriggerEvent::Started, this, &ThisClass::OnGameReset);
    }
}

void ASG_GameMode::OnMoveForward(const FInputActionValue& Value)
{
    float InputValue = Value.Get<float>();
    if (InputValue == 0.0) return;
    SnakeInput = SnakeGame::Input{0, static_cast<int8>(InputValue)};
}

void ASG_GameMode::OnMoveRight(const FInputActionValue& Value)
{
    float InputValue = Value.Get<float>();
    if (InputValue == 0.0) return;
    SnakeInput = SnakeGame::Input{static_cast<int8>(InputValue), 0};
}

void ASG_GameMode::OnGameReset(const FInputActionValue& Value)
{
    if (const bool InputValue = Value.Get<bool>())
    {
        Game.Reset(new SnakeGame::Game(MakeSettings()));
        check(Game.IsValid());

        check(GridVisual);
        GridVisual->SetModel(Game->grid(), CellSize);

        check(SnakeVisual);
        SnakeVisual->SetModel(Game->snake(), CellSize, Game->grid()->dim());

        SnakeInput = SnakeGame::Input{1, 0};
        NextColor();
    }
}

SnakeGame::Settings ASG_GameMode::MakeSettings() const
{
    SnakeGame::Settings GS;
    GS.gridDims = SnakeGame::Dim{GridDims.X, GridDims.Y};
    GS.gameSpeed = GameSpeed;
    GS.snake.defaultSize = SnakeDefaultSize;
    GS.snake.startPosition = SnakeGame::Position{GridDims.X / 2 + 1, GridDims.Y / 2 + 1};  // @todo: proper way to handle +1
    return GS;
}