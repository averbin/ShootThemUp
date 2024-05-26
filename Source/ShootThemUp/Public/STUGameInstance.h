// ShootThemUp Games. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "STUCoreTypes.h"
#include "STUGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
    FLevelData GetStartupLevel() const { return StartLevel; }
    void SetStartupLevel(const FLevelData& Data) { StartLevel = Data; }

    const TArray<FLevelData>& GetLevelsData() const { return LevelsData; }
    FName GetMainMenuLevelName() const { return MainMenuLevelName; }

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Game", meta = (ToolTip = "Level names must be unique!"))
    TArray<FLevelData> LevelsData;
    UPROPERTY(EditDefaultsOnly, Category = "Game")
    FName MainMenuLevelName = NAME_None;

private:
    FLevelData StartLevel;
};
