// ShootThemUp Games. All rights reserved


#include "Weapon/Components/STUWeaponFXComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
USTUWeaponFXComponent::USTUWeaponFXComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void USTUWeaponFXComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USTUWeaponFXComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USTUWeaponFXComponent::PlayImpactFX(const FHitResult& Hit) 
{
    auto ImpactData = DefaultImpactData;
    if (Hit.PhysMaterial.IsValid())
    {
        const UPhysicalMaterial* Material = Hit.PhysMaterial.Get();
        if (ImpactDataMap.Contains(Material))
        {
            ImpactData = ImpactDataMap[Material];
        }
    }

    // Niagara
    UNiagaraFunctionLibrary::SpawnSystemAtLocation(
        GetWorld(),
        ImpactData.NiagaraEffect,
        Hit.ImpactPoint,
        Hit.ImpactNormal.Rotation());

    // Decal
    auto DecalComponent = UGameplayStatics::SpawnDecalAtLocation(
        GetWorld(),
        ImpactData.DecalData.Material,
        ImpactData.DecalData.Size,
        Hit.ImpactPoint,
        Hit.ImpactNormal.Rotation());
    if (DecalComponent)
    {
        DecalComponent->SetFadeOut(ImpactData.DecalData.LifeTime, ImpactData.DecalData.FadeOutTime);
    }
}