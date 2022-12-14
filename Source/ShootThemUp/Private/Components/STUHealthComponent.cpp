// ShootThemUp Games. All rights reserved


#include "Components/STUHealthComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/Engine.h"
#include "TimerManager.h"

DEFINE_LOG_CATEGORY_STATIC(HealthComponentLog, All, All)

// Sets default values for this component's properties
USTUHealthComponent::USTUHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void USTUHealthComponent::BeginPlay()
{
	Super::BeginPlay();

    SetHealth(MaxHealth);

    if (auto Owner = GetOwner())
    {
        Owner->OnTakeAnyDamage.AddDynamic(this, &USTUHealthComponent::OnTakeAnyDamage);
    }
}

void USTUHealthComponent::OnTakeAnyDamage(
    AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
    if (Damage <= 0.0f || IsDead() || !GetWorld())
        return;

    GetWorld()->GetTimerManager().ClearTimer(HealingTimerHandler);

    SetHealth(FMath::Clamp(Health - Damage, 0.0f, MaxHealth));
    if (IsDead())
    {
        OnDeath.Broadcast();
    }
    else
    {
        if (AutoHealProperties.AutoHeal)
        {
            GetWorld()->GetTimerManager().SetTimer(HealingTimerHandler, this, &USTUHealthComponent::OnAutoHeal,
                AutoHealProperties.HealUpdateTimer, true, AutoHealProperties.HealDelay);
        }
    }
}

void USTUHealthComponent::OnAutoHeal()
{
    if (!GetWorld())
    {
        return;
    }

    if (Health >= MaxHealth)
    {
        GetWorld()->GetTimerManager().ClearTimer(HealingTimerHandler);
        OnHealthChanged.Broadcast(MaxHealth);
        return;
    }

    SetHealth(FMath::Clamp(Health + AutoHealProperties.HealModifier, 0.0f, MaxHealth));
}

void USTUHealthComponent::SetHealth(const float Healing) 
{
    Health = Healing;
    OnHealthChanged.Broadcast(Health);
}