// ShootThemUp Games. All rights reserved


#include "UI/STUPlayerStatsRowWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void USTUPlayerStatsRowWidget::SetPlayerName(const FText& Text)
{
    if (!PlayerNameTextBlock)
        return;
    PlayerNameTextBlock->Text = Text;
}

void USTUPlayerStatsRowWidget::SetKills(const FText& Text) 
{
    if (!KillsTextBlock)
        return;
    KillsTextBlock->Text = Text;
}

void USTUPlayerStatsRowWidget::SetDeaths(const FText& Text) 
{
    if (!DethsTextBlock)
        return;
    DethsTextBlock->Text = Text;
}

void USTUPlayerStatsRowWidget::SetTeam(const FText& Text) 
{
    if (!TeamTextBlock)
        return;
    TeamTextBlock->Text = Text;
}

void USTUPlayerStatsRowWidget::SetPlayerIndicator(bool IsVisible) 
{
    if (!PlayerIndicatorImage)
        return;

    PlayerIndicatorImage->SetVisibility(IsVisible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}

void USTUPlayerStatsRowWidget::SetTeamColor(const FLinearColor& Color) 
{
    if (!TeamImage)
        return;
    TeamImage->SetColorAndOpacity(Color);
}
