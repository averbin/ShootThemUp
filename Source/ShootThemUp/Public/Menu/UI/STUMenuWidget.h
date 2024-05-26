// ShootThemUp Games. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUCoreTypes.h"
#include "STUMenuWidget.generated.h"

class UButton;
class UHorizontalBox;
class USTUGameInstance;
class USTULevelItemWidget;
/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
    virtual void NativeOnInitialized() override;

	UPROPERTY(meta = (BindWidget))
    UButton* StartButton;

    UPROPERTY(meta = (BindWidget))
    UButton* QuitGameButton;

    UPROPERTY(meta = (BindWidget))
    UHorizontalBox* LevelItemsBox;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> LevelItemWidgetClass;

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
