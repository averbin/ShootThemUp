// ShootThemUp Games. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "STUBaseWidget.h"
#include "STUCoreTypes.h"
#include "STUMenuWidget.generated.h"

class UButton;
class UHorizontalBox;
class UWidgetAnimation;
class USTUGameInstance;
class USTULevelItemWidget;
class USoundCue;

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUMenuWidget : public USTUBaseWidget
{
	GENERATED_BODY()
	
protected:
    virtual void NativeOnInitialized() override;
    virtual void OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) override;

	UPROPERTY(meta = (BindWidget))
    UButton* StartButton;

    UPROPERTY(meta = (BindWidget))
    UButton* QuitGameButton;

    UPROPERTY(meta = (BindWidget))
    UHorizontalBox* LevelItemsBox;

    UPROPERTY(Transient, meta = (BindWidgetAnim))
    UWidgetAnimation* HideAnimation;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> LevelItemWidgetClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
    USoundCue* StartGameSound;

private:
    UFUNCTION()
    void OnStartButtonClicked();
    UFUNCTION()
    void OnQuitGameButtonClicked();
    UFUNCTION()
    void OnLevelSelected(const FLevelData& Data);

    void InitLevelItems();
    USTUGameInstance* GetSTUGameInstance() const;


    UPROPERTY()
    TArray<USTULevelItemWidget*> LevelItemWidgets;
};
