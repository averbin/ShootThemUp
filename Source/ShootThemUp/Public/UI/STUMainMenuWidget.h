// ShootThemUp Games. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUMainMenuWidget.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
    virtual void NativeOnInitialized() override;

	UPROPERTY( meta = ( BindWidget ) )
    UButton* GameMenuButton;

private:
    UFUNCTION()
    void OnGameMenuButtonClicked();
};
