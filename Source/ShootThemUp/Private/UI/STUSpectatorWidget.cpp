// ShootThemUp Games. All rights reserved


#include "UI/STUSpectatorWidget.h"
#include "Components/STURespawnComponent.h"
#include "STUUtils.h"

bool USTUSpectatorWidget::GetRespawnTime(int32& CountDownTimer) const
{
    const auto RespawnComponent = STUUtils::GetSTUPlayerController<USTURespawnComponent>(GetOwningPlayer());
    if (!RespawnComponent || !RespawnComponent->IsRespawnInProgress())
        return false;

    CountDownTimer = RespawnComponent->GetRespawnCountDown();

    return true;
}
