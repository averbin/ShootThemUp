// ShootThemUp Games. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUClockComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnTimeChanged, const FString&)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTHEMUP_API USTUClockComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USTUClockComponent();

	UFUNCTION(BlueprintCallable)
    FString GetCurrentTime() const { return CurrentTime; }

	FOnTimeChanged OnTimeChanged;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	UFUNCTION()
    void OnTimeUpdate();

private:
    void SetCurrentTime(const int SecondsPassed);

private:
    FTimerHandle ClockHandle;
    FString CurrentTime;
    int32 Seconds = 0;
};
