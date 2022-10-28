// ShootThemUp Games. All rights reserved


#include "Components/STUWeaponComponent.h"
#include "Weapon/STUBaseWeapon.h"
#include "GameFramework/Character.h"

// Sets default values for this component's properties
USTUWeaponComponent::USTUWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USTUWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

    SpawnWeapon();
}

void USTUWeaponComponent::Fire() 
{
    if (!CurrentWeapon) return;
    CurrentWeapon->Fire();
}

void USTUWeaponComponent::SpawnWeapon()
{
    if (!GetWorld()) return;

    auto Character = Cast<ACharacter>(GetOwner());
    if(!Character) return;

    CurrentWeapon = GetWorld()->SpawnActor<ASTUBaseWeapon>(WeaponClass);
    if (!CurrentWeapon) return;

    FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
    CurrentWeapon->AttachToComponent(Character->GetMesh(), AttachmentRules, WeaponAttachName);
    CurrentWeapon->SetOwner(Character);
}