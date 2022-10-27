// ShootThemUp Games. All rights reserved

#include "Weapon/STUBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUBaseWeapon, All, All)

// Sets default values
ASTUBaseWeapon::ASTUBaseWeapon()
{
    PrimaryActorTick.bCanEverTick = false;

    WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
    WeaponMesh->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void ASTUBaseWeapon::BeginPlay()
{
    Super::BeginPlay();

    check(WeaponMesh);
}

void ASTUBaseWeapon::Fire()
{
    UE_LOG(LogSTUBaseWeapon, Display, TEXT("Fire"));
    MakeShoot();
}

void ASTUBaseWeapon::MakeShoot()
{
    const FTransform SocketTransform = WeaponMesh->GetSocketTransform(SocketName);
    const FVector TraceStart = SocketTransform.GetLocation();
    const FVector ShootDirection = SocketTransform.GetRotation().GetForwardVector();
    const FVector TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;

    DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Blue, false, 3.0f, 0, 3.0f);
}