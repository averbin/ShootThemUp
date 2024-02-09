// ShootThemUp Games. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Pickups/STUBasePickup.h"
#include "STUHealthPickup.generated.h"

/**
 *
 */
UCLASS()
class SHOOTTHEMUP_API ASTUHealthPickup : public ASTUBasePickup
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = "10.0", ClampMax = "100.0"))
    float Healing = 10.f;

private:
    virtual bool GivePickupTo(APawn* PlayerPawn) override;
};
