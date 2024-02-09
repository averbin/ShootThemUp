// ShootThemUp Games. All rights reserved


#include "Pickups/STUHealthPickup.h"
#include "Components/STUHealthComponent.h"
#include "STUUtils.h"
DEFINE_LOG_CATEGORY_STATIC(LogASTUHealthPickup, All, All)

bool ASTUHealthPickup::GivePickupTo(APawn* PlayerPawn)
{
    UE_LOG(LogASTUHealthPickup, Display, TEXT("Health taken"));
    const auto HealthComponent = STUUtils::GetSTUPlayerController<USTUHealthComponent>(PlayerPawn);
    if (!HealthComponent || HealthComponent->IsHealthFull())
    {
        return false;
    }

    HealthComponent->Healing(Healing);
    return true;
}
