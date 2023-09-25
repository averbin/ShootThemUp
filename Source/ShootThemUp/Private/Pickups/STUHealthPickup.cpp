// ShootThemUp Games. All rights reserved


#include "Pickups/STUHealthPickup.h"
DEFINE_LOG_CATEGORY_STATIC(LogASTUHealthPickup, All, All)

bool ASTUHealthPickup::GivePickupTo(APawn* PlayerPawn)
{
    UE_LOG(LogASTUHealthPickup, Display, TEXT("Health taken"));
    return true;
}
