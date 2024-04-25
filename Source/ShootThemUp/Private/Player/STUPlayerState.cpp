// ShootThemUp Games. All rights reserved


#include "Player/STUPlayerState.h"

DEFINE_LOG_CATEGORY_STATIC(LogASTUPlayerState, All, All)

void ASTUPlayerState::LogInfo() 
{
    UE_LOG(LogASTUPlayerState, Display, TEXT(" TeamID: %i, Kills: %i, Deaths: %i"), TeamID, Kills, Deaths);
}
