// ShootThemUp Games. All rights reserved


#include "Components/STUHealthComponent.h"
#include "GameFramework/Actor.h"
#include "Dev/STUIceDamageType.h"
#include "Dev/STUFireDamageType.h"

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

    if (auto Owner = GetOwner())
    {
        Owner->OnTakeAnyDamage.AddDynamic(this, &USTUHealthComponent::OnTakeAnyDamage);
    }
}

void USTUHealthComponent::OnTakeAnyDamage(
    AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
    Health -= Damage;
    UE_LOG(HealthComponentLog, Display, TEXT("Health left: %f, damage %f"), Health, Damage);
    if (DamageType)
    {
        if (DamageType->IsA<USTUFireDamageType>())
        {
            UE_LOG(HealthComponentLog, Error, TEXT("Fire damage received, it's so hot!"));
        }
        else if (DamageType->IsA<USTUIceDamageType>())
        {
            UE_LOG(HealthComponentLog, Display, TEXT("Ice damage received, it's so cold!"));
        }
    }
}