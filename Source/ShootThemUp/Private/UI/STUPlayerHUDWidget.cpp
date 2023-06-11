// ShootThemUp Games. All rights reserved


#include "UI/STUPlayerHUDWidget.h"
#include "Components/STUHealthComponent.h"

float USTUPlayerHUDWidget::GetHealthPercent() const
{
    if (const auto Player = GetOwningPlayerPawn())
    {
        if (const auto Component = Player->GetComponentByClass(USTUHealthComponent::StaticClass()))
        {
            if (const auto HealthComponent = Cast<USTUHealthComponent>(Component))
            {
                return HealthComponent->GetHealthPercent();
            }
        }
    }

    return 0.f;
}