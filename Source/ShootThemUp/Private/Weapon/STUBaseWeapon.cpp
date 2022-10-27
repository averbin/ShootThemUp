// ShootThemUp Games. All rights reserved


#include "Weapon/STUBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUBaseWeapon, All, All)

// Sets default values
ASTUBaseWeapon::ASTUBaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
    WeaponMesh->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void ASTUBaseWeapon::BeginPlay()
{
	Super::BeginPlay();

	check(WeaponMesh);
}

void ASTUBaseWeapon::Fire() 
{
	UE_LOG(LogSTUBaseWeapon, Display, TEXT("Fire"));
}