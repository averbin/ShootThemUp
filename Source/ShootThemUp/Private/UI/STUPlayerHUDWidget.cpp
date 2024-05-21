// ShootThemUp Games. All rights reserved


#include "UI/STUPlayerHUDWidget.h"
#include "Components/STUHealthComponent.h"
#include "Components/STUWeaponComponent.h"
#include "STUUtils.h"

void USTUPlayerHUDWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (GetOwningPlayer())
    {
        GetOwningPlayer()->GetOnNewPawnNotifier().AddUObject(this, &USTUPlayerHUDWidget::OnNewPawn);
        OnNewPawn(GetOwningPlayerPawn());
    }

    if (const auto HealthComponent = GetHealthComponent())
    {
        HealthComponent->OnHealthChanged.AddUObject(this, &USTUPlayerHUDWidget::OnHealthChanged);
    }
}

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

void USTUPlayerHUDWidget::OnNewPawn(APawn* Pawn)
{
    const auto HealthComponent = STUUtils::GetSTUPlayerController<USTUHealthComponent>(Pawn);
    if (HealthComponent && !HealthComponent->OnHealthChanged.IsBoundToObject(this))
    {
        HealthComponent->OnHealthChanged.AddUObject(this, &USTUPlayerHUDWidget::OnHealthChanged);
    }
}

bool USTUPlayerHUDWidget::IsPlayerSpectationg() const 
{
    if (const auto Controller = GetOwningPlayer())
    {
        return Controller->GetStateName() == NAME_Spectating;
    }

    return false;
}

void USTUPlayerHUDWidget::OnHealthChanged(float Health, float Delta)
{
    if (Delta < 0.f)
    {
        OnTakeDamage();
    }
}
