// ShootThemUp Games. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUMenuWidget.generated.h"

class UButton;
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

private:
    UFUNCTION()
    void OnStartButtonClicked();
};
