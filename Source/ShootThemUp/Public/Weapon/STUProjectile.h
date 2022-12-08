// ShootThemUp Games. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUProjectile : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ASTUProjectile();

    void SetShootDirection(const FVector& Direction) { ShootDirection = Direction; }

protected:
    UPROPERTY(VisibleAnywhere, Category = "Weapon")
    USphereComponent* CollisionComponent;
    UPROPERTY(VisibleAnywhere, Category = "Weapon")
    UProjectileMovementComponent* MovementComponent;
    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    float DamageRadious = 300.0f;
    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    float DamageAmount = 50.0f;
    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    float LifeSpan = 5.0f;
    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    bool DoFullDamage = false;
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

private:

    AController* GetController() const;
    UFUNCTION()
    void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, 
        UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
    FVector ShootDirection;
};
