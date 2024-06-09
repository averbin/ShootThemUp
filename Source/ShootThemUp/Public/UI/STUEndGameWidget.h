// ShootThemUp Games. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "STUBaseWidget.h"
#include "STUCoreTypes.h"
#include "STUEndGameWidget.generated.h"

class UVerticalBox;
class UButton;
/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUEndGameWidget : public USTUBaseWidget
{
	GENERATED_BODY()
	

protected:
    UPROPERTY(meta = (BindWidget))
    UVerticalBox* PlayerStatBox;

    UPROPERTY(meta = (BindWidget))
    UButton* ResetLevelButton;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PlayerStatWidgetClass;

    virtual void NativeOnInitialized() override;

private:
    void OnMatchStateChanged(ESTUMatchState State);
    void UpdatePlayerStat();

    UFUNCTION()
    void OnResetLevel();
};
