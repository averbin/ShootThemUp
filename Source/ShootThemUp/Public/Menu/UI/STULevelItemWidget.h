// ShootThemUp Games. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUCoreTypes.h"
#include "STULevelItemWidget.generated.h"

class UButton;
class UImage;
class UTextBlock;
/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTULevelItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    FOnLevelSelectedSignature OnLevelSelected;
    void SetLevelData(const FLevelData& Data);
    FLevelData GetLevelData() const { return LevelData; }
    void SetSelected(bool IsSelected);
	
protected:
    virtual void NativeOnInitialized() override;

    UPROPERTY( meta=( BindWidget ))
    UButton* LevelSelectButton;
    UPROPERTY(meta = (BindWidget))
    UTextBlock* LevelNameTextBlock;
    UPROPERTY(meta = (BindWidget))
    UImage* LevelImage;
    UPROPERTY(meta = (BindWidget))
    UImage* FrameImage;

private:
    FLevelData LevelData;
    UFUNCTION()
    void OnLevelItemClicked();
};
