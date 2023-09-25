// ShootThemUp Games. All rights reserved


#include "Pickups/STUAmmoPickup.h"

#include "Components/STUHealthComponent.h"
#include "Components/STUWeaponComponent.h"
#include "STUUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogASTUAmmoPickup, All, All)

bool ASTUAmmoPickup::GivePickupTo(APawn* PlayerPawn)
{
    const auto HealthComponent = STUUtils::GetSTUPlayerController<USTUHealthComponent>(PlayerPawn);
    if (!HealthComponent || HealthComponent->IsDead())
    {
        return false;
    }

    const auto WeaponComponent = STUUtils::GetSTUPlayerController<USTUWeaponComponent>(PlayerPawn);
    if (!WeaponComponent)
    {
        return false;
    }

    UE_LOG(LogASTUAmmoPickup, Display, TEXT("Ammo was taken"));
    return WeaponComponent->TryToAddAmmo(WeaponType, ClipsAmount);
}
