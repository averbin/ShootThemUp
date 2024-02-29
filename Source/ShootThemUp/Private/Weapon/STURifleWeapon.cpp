// ShootThemUp Games. All rights reserved


#include "Weapon/STURifleWeapon.h"

#include "DrawDebugHelpers.h"
#include "Weapon/Components/STUWeaponFXComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

ASTURifleWeapon::ASTURifleWeapon() 
{
    WeaponFXComponent = CreateDefaultSubobject<USTUWeaponFXComponent>("WeaponFXComponent");
    SocketName = TEXT("MuzzleFlashSocket");
}

void ASTURifleWeapon::StartFire()
{
    if (!GetWorld())
        return;
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
    if (IsAmmoEmpty())
    {
        StopFire();
        return;
    }

    InitMuzzleFX();
    FVector TraceStart;
    FVector TraceEnd;
    if (!GetTraceData(TraceStart, TraceEnd))
    {
        StopFire();
        return;
    }

    FHitResult HitResult;
    MakeHit(HitResult, TraceStart, TraceEnd);

    FVector TraceFXEnd = TraceEnd;
    if (HitResult.bBlockingHit)
    {
        TraceFXEnd = HitResult.ImpactPoint;

        WeaponFXComponent->PlayImpactFX(HitResult);
        MakeDamage(HitResult);
    }

    SpawnTraceFX(GetWorldSocketLocation(), TraceFXEnd);

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

void ASTURifleWeapon::SpawnTraceFX(const FVector& StartPoint, const FVector& EndPoint) 
{
    if (UNiagaraComponent* TraceFXComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), TraceFX, StartPoint))
    {
        TraceFXComponent->SetNiagaraVariableVec3(TraceTargetName, EndPoint);
    }
}