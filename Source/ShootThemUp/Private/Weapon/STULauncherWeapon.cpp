// ShootThemUp Games. All rights reserved


#include "Weapon/STULauncherWeapon.h"

#include "Weapon/STUProjectile.h"
#include "Kismet/GameplayStatics.h"

void ASTULauncherWeapon::StartFire() 
{
    MakeShoot();
}

void ASTULauncherWeapon::MakeShoot()
{
    const FTransform SpawnTransform(FRotator::ZeroRotator, GetWorldSocketLocation());
    auto ProjectTile = UGameplayStatics::BeginDeferredActorSpawnFromClass(GetWorld(), ProjectTileClass, SpawnTransform);

    UGameplayStatics::FinishSpawningActor(ProjectTile, SpawnTransform);
}