// ShootThemUp Games. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "STUPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTUPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
    void SetTeamID(const int32 ID) { TeamID = ID; }
    int32 GetTeamID() const { return TeamID; }

    void SetTeamColor(const FLinearColor& NewColor) { TeamColor = NewColor; }
    FLinearColor GetTeamColor() const { return TeamColor; }

    void AddKills() { ++Kills; }
    int32 GetKills() const { return Kills; }
    void AddDeaths() { ++Deaths; }
    int32 GetDeaths() const { return Deaths; }

    void LogInfo();

private:
    int32 TeamID;
    FLinearColor TeamColor;

    int32 Kills = 0;
    int32 Deaths = 0;
};
