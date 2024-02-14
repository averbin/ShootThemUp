// ShootThemUp Games. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUCoreTypes.h"
#include "STUWeaponFXComponent.generated.h"

class UNiagaraSystem;
class UPhysicalMaterial;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTHEMUP_API USTUWeaponFXComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USTUWeaponFXComponent();

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "FX")
    FImpactData DefaultImpactData;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "FX")
    TMap<UPhysicalMaterial*, FImpactData> ImpactDataMap;
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void PlayImpactFX(const FHitResult& Hit);
};
