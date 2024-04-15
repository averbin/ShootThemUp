// ShootThemUp Games. All rights reserved


#include "AI/Decorators/STUAmmoDecorator.h"
#include "AIController.h"
#include "STUUtils.h"
#include "Components/STUHealthComponent.h"
#include "Components/STUWeaponComponent.h"
#include "Weapon/STUBaseWeapon.h"

USTUAmmoDecorator::USTUAmmoDecorator() 
{
    NodeName = "Need Ammo";
}

bool USTUAmmoDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    const auto Controller = OwnerComp.GetAIOwner();
    if (!Controller)
        return false;
    const auto HealthComponent = STUUtils::GetSTUPlayerController<USTUHealthComponent>(Controller->GetPawn());
    if (!HealthComponent || HealthComponent->IsDead())
        return false;

    const auto WeaponComponent = STUUtils::GetSTUPlayerController<USTUWeaponComponent>(Controller->GetPawn());
    if (!WeaponComponent)
        return false;

    return WeaponComponent->NeedAmmo();
}
