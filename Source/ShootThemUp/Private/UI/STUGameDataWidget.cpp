// ShootThemUp Games. All rights reserved


#include "UI/STUGameDataWidget.h"
#include "../STUGameModeBase.h"
#include "Player/STUPlayerState.h"

int32 USTUGameDataWidget::GetCurrentRoundNum() const
{
    const auto GameMode = GetSTUGameMode();
    return GameMode ? GameMode->GetCurrentRound() : 0;
}

int32 USTUGameDataWidget::GetTotalRounds() const
{
    const auto GameMode = GetSTUGameMode();
    return GameMode ? GameMode->GetGameData().Rounds : 0;
}

int32 USTUGameDataWidget::GetRoundSecondsReminding() const
{
    const auto GameMode = GetSTUGameMode();
    return GameMode ? GameMode->GetRemainingTimeInSeconds() : 0;
}

ASTUGameModeBase* USTUGameDataWidget::GetSTUGameMode() const
{
    return GetWorld() ? Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode()) : nullptr;
}

ASTUPlayerState* USTUGameDataWidget::GetSTUPlayerState() const
{
    return GetOwningPlayer() ? Cast<ASTUPlayerState>(GetOwningPlayer()->PlayerState) : nullptr;
}
