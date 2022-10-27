// ShootThemUp Games. All rights reserved

#include "Components/STUClockComponent.h"
#include <chrono>
DEFINE_LOG_CATEGORY_STATIC(LogSTUClockComponent, All, All)

// Sets default values for this component's properties
USTUClockComponent::USTUClockComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void USTUClockComponent::BeginPlay()
{
	Super::BeginPlay();
    check(GetWorld());

    SetCurrentTime(Seconds);
    GetWorld()->GetTimerManager().SetTimer(
        ClockHandle, this, &USTUClockComponent::OnTimeUpdate, 1.0f,
        true, 0.0f);
}

void USTUClockComponent::OnTimeUpdate() 
{
    ++Seconds;
    SetCurrentTime(Seconds);
    UE_LOG(LogSTUClockComponent, Display, TEXT("%s"), *CurrentTime);
    OnTimeChanged.Broadcast(CurrentTime);
}

void USTUClockComponent::SetCurrentTime(const int SecondsPassed) 
{
    const auto Sec = std::chrono::seconds(SecondsPassed);
    CurrentTime = (FString::Printf(TEXT("%.2d:%.2d"), std::chrono::duration_cast<std::chrono::minutes>(Sec).count() % 60,
        std::chrono::duration_cast<std::chrono::seconds>(Sec).count() % 60));
}
