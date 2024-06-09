// ShootThemUp Games. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "STUBaseWidget.h"
#include "STUCoreTypes.h"
#include "STUPlayerHUDWidget.generated.h"

class USTUWeaponComponent;
class USTUHealthComponent;
class UProgressBar;
    /**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUPlayerHUDWidget : public USTUBaseWidget
{
	GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, Category = "UI")
    float GetHealthPercent() const;
    UFUNCTION(BlueprintCallable, Category = "UI")
    bool GetWeaponUIData(FWeaponUIData& UIData) const;
    UFUNCTION(BlueprintCallable, Category = "UI")
    bool GetWeaponAmmoData(FAmmoData& AmmoData) const;
    UFUNCTION(BlueprintCallable, Category = "UI")
    bool IsPlayerAlive() const;
    UFUNCTION(BlueprintCallable, Category = "UI")
    bool IsPlayerSpectationg() const;
    UFUNCTION(BlueprintImplementableEvent, Category = "UI")
    void OnTakeDamage();
    UFUNCTION(BlueprintCallable, Category = "UI")
    int32 GetKillsNum() const;

protected:
    UPROPERTY( meta = (BindWidget))
    UProgressBar* HealthProgressBar;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    float PercentColorThreshold = 0.3f;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    FLinearColor DefaultHealthColor = FLinearColor::White;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    FLinearColor CriticalHealthColor = FLinearColor::Red;

    virtual void NativeOnInitialized() override;

private:
    void OnHealthChanged(float Health, float Delta);
    USTUWeaponComponent* GetWeaponComponent() const;
    USTUHealthComponent* GetHealthComponent() const;
    void OnNewPawn(APawn* Pawn);
    void UpdateHealthBar();
};
