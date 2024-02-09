// ShootThemUp Games. All rights reserved


#include "Pickups/STUBasePickup.h"
#include "Components/SphereComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogBasePickup, All, All)

// Sets default values
ASTUBasePickup::ASTUBasePickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("CollisionComponent");
    CollisionComponent->InitSphereRadius(50.0);
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    SetRootComponent(CollisionComponent);
}

// Called when the game starts or when spawned
void ASTUBasePickup::BeginPlay()
{
	Super::BeginPlay();
	
    GenerateRotationYaw();
}

// Called every frame
void ASTUBasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    AddActorLocalRotation(FRotator(0.f, RotationYaw, 0.f));
}

void ASTUBasePickup::NotifyActorBeginOverlap(AActor* OtherActor) 
{
    Super::NotifyActorBeginOverlap(OtherActor);

    if (const auto PlayerPawn = Cast<APawn>(OtherActor))
    {
        if (GivePickupTo(PlayerPawn))
        {
            UE_LOG(LogBasePickup, Display, TEXT("Pickup was taken"));
            PickupWasTaken();
        }
    }
}

bool ASTUBasePickup::GivePickupTo(APawn* PlayerPawn)
{
    return false;
}

void ASTUBasePickup::SetCollisionAndVisability(const ECollisionResponse CollisionType, const bool IsVisible)
{
    CollisionComponent->SetCollisionResponseToAllChannels(CollisionType);
    if (GetRootComponent())
    {
        GetRootComponent()->SetVisibility(IsVisible, true);
    }
}

void ASTUBasePickup::PickupWasTaken()
{
    SetCollisionAndVisability(ECollisionResponse::ECR_Ignore, false);
    FTimerHandle RespawnTimerHandler;
    GetWorldTimerManager().SetTimer(RespawnTimerHandler, this, &ASTUBasePickup::Respawn, RespawnTime);
}

void ASTUBasePickup::Respawn()
{
    SetCollisionAndVisability(ECollisionResponse::ECR_Overlap, true);
    GenerateRotationYaw();
}

void ASTUBasePickup::GenerateRotationYaw() 
{
    const auto Direction = FMath::RandBool() ? 1.f : -1.f;
    RotationYaw = FMath::RandRange(1.f, 2.f) * Direction;
}