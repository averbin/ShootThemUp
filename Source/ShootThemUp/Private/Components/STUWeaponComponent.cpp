// ShootThemUp Games. All rights reserved


#include "Components/STUWeaponComponent.h"
#include "Weapon/STUBaseWeapon.h"
#include "GameFramework/Character.h"
#include "Animations/STUEquipFinishedAnimNotify.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponComponent, All, All);

// Sets default values for this component's properties
USTUWeaponComponent::USTUWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USTUWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

    InitAnimations();
    SpawnWeapons();
    EquipWeapon(CurrentWeaponIndex);
}

void USTUWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason) 
{
    CurrentWeapon = nullptr;
    for (auto Weapon : Weapons)
    {
        Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
        Weapon->Destroy();
    }
    Weapons.Empty();

    Super::EndPlay(EndPlayReason);
}

void USTUWeaponComponent::StartFire() 
{
    if (!CanFire()) return;
    CurrentWeapon->StartFire();
}

void USTUWeaponComponent::StopFire() 
{
    if (!CurrentWeapon) return;
    CurrentWeapon->StopFire();
}

void USTUWeaponComponent::SpawnWeapons()
{
    if (!GetWorld()) return;

    auto Character = Cast<ACharacter>(GetOwner());
    if(!Character) return;

    for (auto OneWeaponData : WeaponData)
    {
        auto Weapon = GetWorld()->SpawnActor<ASTUBaseWeapon>(OneWeaponData.WeaponClass);
        if (!Weapon)
            continue;
        Weapon->SetOwner(Character);
        Weapons.Add(Weapon);

        AttachWeaponToSocket(Weapon, Character->GetMesh(), WeaponArmorySocketName);
    }
}

void USTUWeaponComponent::EquipWeapon(const int32 WeaponIndex) 
{
    if (WeaponIndex < 0 || WeaponIndex >= Weapons.Num())
    {
        UE_LOG(LogWeaponComponent, Error, TEXT("Invalid weapon index!"));
        return;
    }

    auto Character = Cast<ACharacter>(GetOwner());
    if (!Character)
        return;

    if (CurrentWeapon)
    {
        CurrentWeapon->StopFire();
        AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponArmorySocketName);
    }

    CurrentWeapon = Weapons[WeaponIndex];
    //CurrentReloadAnimMontage = WeaponData[WeaponIndex].ReloadAnimMontage;
    const auto CurrentWeaponData = WeaponData.FindByPredicate([&](const FWeaponData& Data) {
        return Data.WeaponClass == CurrentWeapon->GetClass();
    });

    CurrentReloadAnimMontage = CurrentWeaponData ? CurrentWeaponData->ReloadAnimMontage : nullptr;

    AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponEquipSocketName);
    EquipAnimInProgress = true;
    PlayAnimMontage(EquipMontage);
}

void USTUWeaponComponent::AttachWeaponToSocket(ASTUBaseWeapon* Weapon, USceneComponent* SckeletonMesh, const FName& SocketName)
{
    if (!Weapon || !SckeletonMesh)
        return;
    FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
    Weapon->AttachToComponent(SckeletonMesh, AttachmentRules, SocketName);
}

void USTUWeaponComponent::NextWeapon() 
{
    if (CanEquip())
    {
        CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
        EquipWeapon(CurrentWeaponIndex);
    }
}

void USTUWeaponComponent::Reload() 
{
    PlayAnimMontage(CurrentReloadAnimMontage);
}

void USTUWeaponComponent::PlayAnimMontage(UAnimMontage* Animation) 
{
    auto Character = Cast<ACharacter>(GetOwner());
    if (!Character)
        return;

    Character->PlayAnimMontage(Animation);
}

void USTUWeaponComponent::InitAnimations()
{
    if (!EquipMontage)
        return;

    const auto NotifyEvents = EquipMontage->Notifies;

    for (auto NotifyEvent : NotifyEvents)
    {
        if (auto EquipFinishedNotify = Cast<USTUEquipFinishedAnimNotify>(NotifyEvent.Notify))
        {
            EquipFinishedNotify->OnNotified.AddUObject(this, &USTUWeaponComponent::OnEquipFinished);
            break;
        }
    }
}

void USTUWeaponComponent::OnEquipFinished(USkeletalMeshComponent* MeshComp)
{
    if (ACharacter* Character = Cast<ACharacter>(GetOwner()))
    {
        if (Character->GetMesh() == MeshComp)
        {
            UE_LOG(LogWeaponComponent, Display, TEXT("Equip is Finished"));
            EquipAnimInProgress = false;
        }
    }
}

bool USTUWeaponComponent::CanFire() const
{
    return CurrentWeapon && !EquipAnimInProgress;
}

bool USTUWeaponComponent::CanEquip() const
{
    return !EquipAnimInProgress;
}
