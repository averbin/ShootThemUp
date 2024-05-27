// ShootThemUp Games. All rights reserved


#include "UI/STUHealthbarWidget.h"
#include "Components/ProgressBar.h"

void USTUHealthbarWidget::SetHealthPercent(float Percent)
{
    if (!HealthProgressBar)
        return;

    const auto HealthBarVisibility = (Percent > PercentVisabilityThreshold || FMath::IsNearlyZero(Percent)) 
        ? ESlateVisibility::Hidden : ESlateVisibility::Visible;
    HealthProgressBar->SetVisibility(HealthBarVisibility);

    const auto HealthBarColor = Percent > PercentColorThreshold ? GoodColor : BadColor;

    HealthProgressBar->SetFillColorAndOpacity(HealthBarColor);
    HealthProgressBar->SetPercent(Percent);
}
