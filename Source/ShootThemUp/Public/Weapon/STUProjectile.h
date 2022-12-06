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
    UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
    USphereComponent* CollisionComponent;
    UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
    UProjectileMovementComponent* MovementComponent;
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

private:
    FVector ShootDirection;
};
