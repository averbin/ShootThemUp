// ShootThemUp Games. All rights reserved


#include "AI/Tasks/STUNextLocationTask.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "NavigationSystem.h"

USTUNextLocationTask::USTUNextLocationTask()
{
    NodeName = "Next Location";
}

EBTNodeResult::Type USTUNextLocationTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) 
{
    const auto Controller = OwnerComp.GetAIOwner();
    const auto Blackboard = OwnerComp.GetBlackboardComponent();

    if (!Controller || !Blackboard)
        return EBTNodeResult::Type::Failed;

    const auto Pawn = Controller->GetPawn();
    if (!Pawn)
        return EBTNodeResult::Type::Failed;

    const auto NavSys = UNavigationSystemV1::GetCurrent(Pawn);
    if (!NavSys)
        return EBTNodeResult::Type::Failed;

    FNavLocation NavLocation;
    const auto Found = NavSys->GetRandomPointInNavigableRadius(Pawn->GetActorLocation(), Radious, NavLocation);
    if (!Found)
        return EBTNodeResult::Type::Failed;

    Blackboard->SetValueAsVector(AimLocationKey.SelectedKeyName, NavLocation.Location);

    return EBTNodeResult::Type::Succeeded;
}