// ShootThemUp Games. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/ActorComponent.h"
#include "STUHealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeath)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float)

USTRUCT(BlueprintType) 
struct FAutoHealProperties
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal")
    bool AutoHeal = true;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = "AutoHeal"))
    float HealUpdateTimer = 1.0f;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = "AutoHeal"))
    float HealDelay = 3.0f;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = "AutoHeal"))
    float HealModifier = 4.0f;
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHOOTTHEMUP_API USTUHealthComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USTUHealthComponent();

    float GetHealth() const { return Health; }
    
    UFUNCTION(BlueprintCallable)
    bool IsDead() const { return Health <= 0.0f; }
    UFUNCTION()
    void OnAutoHeal();

    FOnDeath OnDeath;
    FOnHealthChanged OnHealthChanged;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "1.0", ClampMax = "100.0"))
    float MaxHealth = 100.0f;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal")
    FAutoHealProperties AutoHealProperties;
    // Called when the game starts
    virtual void BeginPlay() override;

private:
    float Health = 0.0f;
    FTimerHandle HealingTimerHandler;
    UFUNCTION()
    void OnTakeAnyDamage(
        AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);
    void SetHealth(const float Healing);
};
