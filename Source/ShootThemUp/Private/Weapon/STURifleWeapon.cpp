// ShootThemUp Games. All rights reserved


#include "Weapon/STURifleWeapon.h"

#include "DrawDebugHelpers.h"
#include "Weapon/Components/STUWeaponFXComponent.h"
#include "NiagaraComponent.h"

ASTURifleWeapon::ASTURifleWeapon() 
{
    WeaponFXComponent = CreateDefaultSubobject<USTUWeaponFXComponent>("WeaponFXComponent");
    SocketName = TEXT("MuzzleFlashSocket");
}

void ASTURifleWeapon::StartFire()
{
    if (!GetWorld())
        return;
    InitMuzzleFX();
    GetWorld()->GetTimerManager().SetTimer(ShootTimerHandle, this, &ASTURifleWeapon::MakeShoot, TimeBetweenShots, true);
}

void ASTURifleWeapon::StopFire()
{
    GetWorld()->GetTimerManager().ClearTimer(ShootTimerHandle);
    SetMuzzleFXVisability(false);
}

void ASTURifleWeapon::BeginPlay() 
{
    Super::BeginPlay();
    check(WeaponFXComponent);
}

void ASTURifleWeapon::MakeShoot()
{
    if (!GetWorld() && !IsAmmoEmpty())
    {
        StopFire();
        return;
    }

    FVector TraceStart;
    FVector TraceEnd;
    if (!GetTraceData(TraceStart, TraceEnd))
    {
        StopFire();
        return;
    }

    FHitResult HitResult;
    MakeHit(HitResult, TraceStart, TraceEnd);

    if (HitResult.bBlockingHit)
    {
        //DrawDebugLine(GetWorld(), GetWorldSocketLocation(), HitResult.ImpactPoint, FColor::Blue, false, 3.0f, 0, 3.0f);
        //DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 20.0f, FColor::Red, false, 5.0f);
        WeaponFXComponent->PlayImpactFX(HitResult);
        MakeDamage(HitResult);
    }
    else
    {
        DrawDebugLine(GetWorld(), GetWorldSocketLocation(), TraceEnd, FColor::Blue, false, 3.0f, 0, 3.0f);
    }

    DecreaseAmmo();
}

bool ASTURifleWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd)
{
    FVector ViewLocation;
    FRotator ViewRotation;

    if (GetPlayerViewPoint(ViewLocation, ViewRotation))
    {
        TraceStart = ViewLocation;
        const auto HalfRad = FMath::DegreesToRadians(BulletsSpread);
        const FVector ShootDirection = FMath::VRandCone(ViewRotation.Vector(), HalfRad);
        TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
        return true;
    }

    return false;
}

void ASTURifleWeapon::MakeDamage(FHitResult& HitResult)
{
    if (const auto Actor = HitResult.GetActor())
    {
        Actor->TakeDamage(DamageAmount, FDamageEvent(), GetPlayerController(), this);
    }
}

void ASTURifleWeapon::InitMuzzleFX() 
{
    if (!MuzzleFXComponent)
    {
        MuzzleFXComponent = SpawnMuzzleFX();
    }
    SetMuzzleFXVisability(true);
}

void ASTURifleWeapon::SetMuzzleFXVisability(bool Visible) 
{
    if (MuzzleFXComponent)
    {
        MuzzleFXComponent->SetPaused(!Visible);
        MuzzleFXComponent->SetVisibility(Visible, true);
    }
}