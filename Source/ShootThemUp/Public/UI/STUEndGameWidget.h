// ShootThemUp Games. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUCoreTypes.h"
#include "STUEndGameWidget.generated.h"

class UVerticalBox;
/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUEndGameWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
    virtual bool Initialize() override;

protected:
    UPROPERTY(meta = (BindWidget))
    UVerticalBox* PlayerStatBox;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PlayerStatWidgetClass;

private:
    void OnMatchStateChanged(ESTUMatchState State);
    void UpdatePlayerStat();
};
