// Snake Game, Copyright moonabyss. Al Rights Reserved.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"

#include "SG_GameOverWidget.generated.h"

class UButton;
class UTextBlock;

UCLASS()
class SNAKEGAME_API USG_GameOverWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    void SetScore(uint32 Score);
    void SetResetGameKeyName(const FString& ResetGameKeyName);

protected:
    virtual void NativeOnInitialized() override;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> ScoreText;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> RestartGameText;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> BackToMenuButton;

    UPROPERTY(EditDefaultsOnly)
    TSoftObjectPtr<UWorld> MenuLevel;

private:
    UFUNCTION()
    void OnBackToMenu();
};
