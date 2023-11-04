// Snake Game, Copyright moonabyss. Al Rights Reserved.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"

#include "SG_GameplayWidget.generated.h"

class UTextBlock;

UCLASS()
class SNAKEGAME_API USG_GameplayWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    void SetGameTime(float Seconds);
    void SetScore(uint32 Score);
    void SetResetGameKeyName(const FString& ResetGameKeyName);

protected:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> TimeText;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> ScoreText;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> RestartGameText;
};
