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

    Health = MaxHealth;

    OnHealthChanged.Broadcast(Health);

    if (auto Owner = GetOwner())
    {
        Owner->OnTakeAnyDamage.AddDynamic(this, &USTUHealthComponent::OnTakeAnyDamage);
        Owner->OnActorBeginOverlap.AddDynamic(this, &USTUHealthComponent::OnActorEndOverlap);
    }
}

void USTUHealthComponent::OnTakeAnyDamage(
    AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
    if (Damage <= 0.0f || IsDead())
        return;
    Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);
    OnHealthChanged.Broadcast(Health);
    if (IsDead())
    {
        OnDeath.Broadcast();
    }
}

void USTUHealthComponent::OnActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor) 
{
    UE_LOG(HealthComponentLog, Error, TEXT("Collission is finished"));
    if (AutoHealProperties.AutoHeal)
    {
        GetWorld()->GetTimerManager().SetTimer(
            TimerHandler, this, &USTUHealthComponent::OnAutoHeal, AutoHealProperties.HealUpdateTimer, true, AutoHealProperties.HealDelay);
    }
}

void USTUHealthComponent::OnAutoHeal()
{
    if (Health >= MaxHealth)
    {
        GetWorld()->GetTimerManager().ClearTimer(TimerHandler);
        OnHealthChanged.Broadcast(MaxHealth);
        return;
    }
    Health = FMath::Clamp(Health + AutoHealProperties.HealModifier, 0.0f, MaxHealth);
    OnHealthChanged.Broadcast(Health);
}