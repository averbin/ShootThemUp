// ShootThemUp Games. All rights reserved


#include "Weapon/STULauncherWeapon.h"

#include "Weapon/STUProjectile.h"

void ASTULauncherWeapon::StartFire() 
{
    MakeShoot();
}

void ASTULauncherWeapon::MakeShoot()
{
    if (!GetWorld() || IsAmmoEmpty())
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

    const FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
    const FVector Direction = (EndPoint - GetWorldSocketLocation()).GetSafeNormal();

    const FTransform SpawnTransform(FRotator::ZeroRotator, GetWorldSocketLocation());
    if (auto ProjectTile = GetWorld()->SpawnActorDeferred<ASTUProjectile>(ProjectTileClass, SpawnTransform))
    {
        ProjectTile->SetShootDirection(Direction);
        ProjectTile->SetOwner(GetOwner());
        ProjectTile->FinishSpawning(SpawnTransform);
    }

    DecreaseAmmo();
}