// ShootThemUp Games. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUHealthbarWidget.generated.h"

class UProgressBar;
/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUHealthbarWidget : public UUserWidget
{
	GENERATED_BODY()
public:
    void SetHealthPercent(float Percent);

protected:
    UPROPERTY( meta=( BindWidget ) )
    UProgressBar* HealthProgressBar;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    float PercentVisabilityThreshold = 0.8f;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    float PercentColorThreshold = 0.3f;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    FLinearColor GoodColor = FLinearColor::White;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    FLinearColor BadColor = FLinearColor::Red;
};
