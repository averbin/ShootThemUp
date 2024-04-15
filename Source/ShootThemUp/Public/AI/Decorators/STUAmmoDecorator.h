// ShootThemUp Games. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "STUAmmoDecorator.generated.h"

class ASTUBaseWeapon;

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUAmmoDecorator : public UBTDecorator
{
	GENERATED_BODY()
	
public:
    USTUAmmoDecorator();

protected:
    virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    TSubclassOf<ASTUBaseWeapon> WeaponType;
};
