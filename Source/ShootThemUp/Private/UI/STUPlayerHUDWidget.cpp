// ShootThemUp Games. All rights reserved


#include "UI/STUPlayerHUDWidget.h"
#include "Components/STUHealthComponent.h"
#include "Components/STUWeaponComponent.h"

float USTUPlayerHUDWidget::GetHealthPercent() const
{
    if (const auto HealthComponent = GetHealthComponent())
    {
        return HealthComponent->GetHealthPercent();
    }

    return 0.f;
}

bool USTUPlayerHUDWidget::GetWeaponUIData(FWeaponUIData& UIData) const
{
    if (const auto WeaponComponent = GetWeaponComponent())
    {
        return WeaponComponent->GetWeaponUIData(UIData);
    }

    return false;
}

bool USTUPlayerHUDWidget::GetWeaponAmmoData(FAmmoData& AmmoData) const
{
    if (const auto WeaponComponent = GetWeaponComponent())
    {
        return WeaponComponent->GetWeaponAmmoData(AmmoData);
    }

    return false;
}

USTUWeaponComponent* USTUPlayerHUDWidget::GetWeaponComponent() const
{
    if (const auto Player = GetOwningPlayerPawn())
    {
        if (const auto Component = Player->GetComponentByClass(USTUWeaponComponent::StaticClass()))
        {
            return Cast<USTUWeaponComponent>(Component);
        }
    }

    return nullptr;
}

bool USTUPlayerHUDWidget::IsPlayerAlive() const 
{
    if (auto HealthComponent = GetHealthComponent())
    {
        return !HealthComponent->IsDead();
    }

    return false;
}

USTUHealthComponent* USTUPlayerHUDWidget::GetHealthComponent() const
{
    if (const auto Player = GetOwningPlayerPawn())
    {
        if (const auto Component = Player->GetComponentByClass(USTUHealthComponent::StaticClass()))
        {
            return Cast<USTUHealthComponent>(Component);
        }
    }

    return nullptr;
}

bool USTUPlayerHUDWidget::IsPlayerSpectationg() const 
{
    if (const auto Controller = GetOwningPlayer())
    {
        return Controller->GetStateName() == NAME_Spectating;
    }

    return false;
}