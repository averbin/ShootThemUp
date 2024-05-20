// ShootThemUp Games. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUPlayerStatsRowWidget.generated.h"

class UImage;
class UTextBlock;
/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUPlayerStatsRowWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    void SetPlayerName(const FText& Text);
    void SetKills(const FText& Text);
    void SetDeaths(const FText& Text);
    void SetTeam(const FText& Text);
    void SetPlayerIndicator(bool IsVisible);
	
protected:
    UPROPERTY(meta = (BindWidget))
    UTextBlock* PlayerNameTextBlock;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* KillsTextBlock;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* DethsTextBlock;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* TeamTextBlock;

    UPROPERTY(meta = (BindWidget))
    UImage* PlayerIndicatorImage;
};
