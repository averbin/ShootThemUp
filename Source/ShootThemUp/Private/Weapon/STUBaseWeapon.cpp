// ShootThemUp Games. All rights reserved

#include "Weapon/STUBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"

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

void ASTUBaseWeapon::StartFire()
{
}

void ASTUBaseWeapon::StopFire() 
{
}

void ASTUBaseWeapon::MakeShoot()
{
}

APlayerController* ASTUBaseWeapon::GetPlayerController() const 
{
    if (const auto Player = Cast<ACharacter>(GetOwner()))
        return Player->GetController<APlayerController>();

    return nullptr;
}

bool ASTUBaseWeapon::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation)
{
    if (const auto Controller = GetPlayerController())
    {
        Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
        return true;
    }
    return false;
}

FVector ASTUBaseWeapon::GetWorldSocketLocation() const 
{
    return WeaponMesh->GetSocketLocation(SocketName);
}

bool ASTUBaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) 
{
    FVector ViewLocation;
    FRotator ViewRotation;

    if (GetPlayerViewPoint(ViewLocation, ViewRotation))
    {
        TraceStart = ViewLocation;
        const FVector ShootDirection = ViewRotation.Vector();
        TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
        return true;
    }

    return false;
}

void ASTUBaseWeapon::MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd) 
{
    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(GetOwner());

    GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionParams);
}