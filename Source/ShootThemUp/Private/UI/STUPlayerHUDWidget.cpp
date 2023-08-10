// ShootThemUp Games. All rights reserved


#include "UI/STUPlayerHUDWidget.h"
#include "Components/STUHealthComponent.h"
#include "Components/STUWeaponComponent.h"
#include "STUUtils.h"

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
    return STUUtils::GetSTUPlayerController<USTUWeaponComponent>(GetOwningPlayerPawn());
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
    return STUUtils::GetSTUPlayerController<USTUHealthComponent>(GetOwningPlayerPawn());
}

bool USTUPlayerHUDWidget::IsPlayerSpectationg() const 
{
    if (const auto Controller = GetOwningPlayer())
    {
        return Controller->GetStateName() == NAME_Spectating;
    }

    return false;
}