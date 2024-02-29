// ShootThemUp Games. All rights reserved


#include "AI/Services/STUChangeWeaponService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "STUUtils.h"
#include "Components/STUWeaponComponent.h"

USTUChangeWeaponService::USTUChangeWeaponService() 
{
    NodeName = "Change Weapon";
}

void USTUChangeWeaponService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) 
{
    const auto Controller = OwnerComp.GetAIOwner();

    if (Controller)
    {
        if (const auto WeaponComponent = STUUtils::GetSTUPlayerController<USTUWeaponComponent>(Controller->GetPawn()))
        {
            if (Probability > 0.0f && FMath::FRand() <= Probability)
            {
                WeaponComponent->NextWeapon();
            }
        }
    }
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}