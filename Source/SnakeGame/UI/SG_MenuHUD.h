// Snake Game, Copyright moonabyss. Al Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"

#include "SG_MenuHUD.generated.h"

class USG_StartGameWidget;

UCLASS()
class SNAKEGAME_API ASG_MenuHUD : public AHUD
{
    GENERATED_BODY()

protected:
    virtual void BeginPlay() override;

    UPROPERTY(Category = "UI", EditDefaultsOnly)
    TSubclassOf<USG_StartGameWidget> StartGameWidgetClass;

private:
    UPROPERTY()
    TObjectPtr<USG_StartGameWidget> StartGameWidget;
};
