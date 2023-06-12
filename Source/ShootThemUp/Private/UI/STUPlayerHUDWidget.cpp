// ShootThemUp Games. All rights reserved


#include "UI/STUPlayerHUDWidget.h"
#include "Components/STUHealthComponent.h"
#include "Components/STUWeaponComponent.h"

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

bool USTUPlayerHUDWidget::GetWeaponUIData(FWeaponUIData& UIData) const
{
    if (const auto Player = GetOwningPlayerPawn())
    {
        if (const auto Component = Player->GetComponentByClass(USTUWeaponComponent::StaticClass()))
        {
            if (const auto WeaponComponent = Cast<USTUWeaponComponent>(Component))
            {
                return WeaponComponent->GetWeaponUIData(UIData);
            }
        }
    }
    return false;
}
