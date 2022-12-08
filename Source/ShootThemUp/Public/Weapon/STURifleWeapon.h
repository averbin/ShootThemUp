// ShootThemUp Games. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STUBaseWeapon.h"
#include "STURifleWeapon.generated.h"

/**
 *
 */
UCLASS()
class SHOOTTHEMUP_API ASTURifleWeapon : public ASTUBaseWeapon
{
    GENERATED_BODY()

public:
    virtual void StartFire() override;
    virtual void StopFire() override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float TimeBetweenShots = 0.1f;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float BulletsSpread = 1.5f;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
    float DamageAmount = 10.0f;

    virtual void MakeShoot() override;
    virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) override;

private:
    void MakeDamage(FHitResult& HitResult);
    FTimerHandle ShootTimerHandle;
};
