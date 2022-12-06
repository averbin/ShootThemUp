// ShootThemUp Games. All rights reserved

#include "Weapon/STUProjectile.h"

#include "Components/SphereComponent.h"

#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ASTUProjectile::ASTUProjectile()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

    CollisionComponent = CreateDefaultSubobject<USphereComponent>("CollisionComponent");
    CollisionComponent->InitSphereRadius(5.0);
    SetRootComponent(CollisionComponent);

    MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComponent");
    MovementComponent->InitialSpeed = 3000.0f;
    MovementComponent->ProjectileGravityScale = 0.0f;
}

// Called when the game starts or when spawned
void ASTUProjectile::BeginPlay()
{
    Super::BeginPlay();

    check(CollisionComponent);
    check(MovementComponent);

    MovementComponent->Velocity = ShootDirection * MovementComponent->InitialSpeed;
    SetLifeSpan(5.0f);
}