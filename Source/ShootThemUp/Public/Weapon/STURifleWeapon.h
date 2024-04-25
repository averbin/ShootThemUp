// ShootThemUp Games. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STUBaseWeapon.h"
#include "STURifleWeapon.generated.h"

class USTUWeaponFXComponent;
class UNiagaraComponent;
class UNiagaraSystem;

UCLASS()
class SHOOTTHEMUP_API ASTURifleWeapon : public ASTUBaseWeapon
{
    GENERATED_BODY()

public:
    ASTURifleWeapon();

    virtual void StartFire() override;
    virtual void StopFire() override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float TimeBetweenShots = 0.1f;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float BulletsSpread = 1.5f;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
    float DamageAmount = 10.0f;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    USTUWeaponFXComponent* WeaponFXComponent;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    UNiagaraSystem* TraceFX;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    FString TraceTargetName = "TraceTarget";

    virtual void BeginPlay() override;
    virtual void MakeShoot() override;
    virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) override;

private:
    UPROPERTY()
    UNiagaraComponent* MuzzleFXComponent;
    void MakeDamage(FHitResult& HitResult);
    FTimerHandle ShootTimerHandle;

    void InitMuzzleFX();
    void SetMuzzleFXVisability(bool Visible);
    void SpawnTraceFX(const FVector& StartPoint, const FVector& EndPoint);
    AController* GetController() const;
};
