// ShootThemUp Games. All rights reserved


#include "Components/STURespawnComponent.h"
#include "../STUGameModeBase.h"

DEFINE_LOG_CATEGORY_STATIC(LogUSTURespawnComponent, Display, Display)

// Sets default values for this component's properties
USTURespawnComponent::USTURespawnComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void USTURespawnComponent::Respawn(int32 RespawnTime) 
{
    if (!GetWorld())
        return;
    RespawnCountDown = RespawnTime;
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &USTURespawnComponent::RespawnTimerUpdate, 1.0f, true);
}


// Called when the game starts
void USTURespawnComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USTURespawnComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USTURespawnComponent::RespawnTimerUpdate() 
{
    if (--RespawnCountDown)
    {
        if (!GetWorld())
            return;
        GetWorld()->GetTimerManager().ClearTimer(TimerHandle);

        const auto GameMode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());
        if (!GameMode)
            return;
        GameMode->RespawnRequest(Cast<AController>(GetOwner()));
    }
}

