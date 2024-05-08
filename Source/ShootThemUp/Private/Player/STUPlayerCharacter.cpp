// ShootThemUp Games. All rights reserved


#include "Player/STUPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/STUCharactermovementComponent.h"
#include "Components/STUWeaponComponent.h"
#include "Components/STUHealthComponent.h"
#include "GameFramework/SpringArmComponent.h"

ASTUPlayerCharacter::ASTUPlayerCharacter(const FObjectInitializer& ObjInit)
    : Super(ObjInit)
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
    SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->bUsePawnControlRotation = true;
    SpringArmComponent->SocketOffset = FVector(0.0f, 100.0f, 80.0f);

    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(SpringArmComponent);

    CameraCollision = CreateDefaultSubobject<USphereComponent>("CameraCollision");
    CameraCollision->SetupAttachment(CameraComponent);
    CameraCollision->SetSphereRadius(10.f);
    CameraCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
}

// Called to bind functionality to input
void ASTUPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    check(PlayerInputComponent) check(WeaponComponent);

    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASTUPlayerCharacter::Jump);
    PlayerInputComponent->BindAxis("MoveForward", this, &ASTUPlayerCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ASTUPlayerCharacter::MoveRight);

    PlayerInputComponent->BindAxis("LookUp", this, &ASTUBaseCharacter::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("TurnAround", this, &ASTUBaseCharacter::AddControllerYawInput);

    PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ASTUPlayerCharacter::OnStartRunning);
    PlayerInputComponent->BindAction("Run", IE_Released, this, &ASTUPlayerCharacter::OnStopRunning);

    PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &USTUWeaponComponent::StartFire);
    PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &USTUWeaponComponent::StopFire);
    PlayerInputComponent->BindAction("NextWeapon", IE_Released, WeaponComponent, &USTUWeaponComponent::NextWeapon);
    PlayerInputComponent->BindAction("Reload", IE_Released, WeaponComponent, &USTUWeaponComponent::Reload);
}

void ASTUPlayerCharacter::MoveForward(float Amount)
{
    IsMovingForward = Amount > 0.0f;
    if (Amount == 0.0f)
        return;
    AddMovementInput(GetActorForwardVector(), Amount);
}

void ASTUPlayerCharacter::MoveRight(float Amount)
{
    if (Amount == 0.0f)
        return;
    AddMovementInput(GetActorRightVector(), Amount);
}

bool ASTUPlayerCharacter::IsRunning() const
{
    return WantsToRun && IsMovingForward && !GetVelocity().IsZero();
}

void ASTUPlayerCharacter::OnStartRunning()
{
    WantsToRun = true;
}

void ASTUPlayerCharacter::OnStopRunning()
{
    WantsToRun = false;
}

void ASTUPlayerCharacter::OnDeath()
{
    Super::OnDeath();
    if (Controller)
    {
        Controller->ChangeState(NAME_Spectating);
    }
}

void ASTUPlayerCharacter::BeginPlay() 
{
    Super::BeginPlay();

    check(CameraCollision);

    CameraCollision->OnComponentBeginOverlap.AddDynamic(this, &ASTUPlayerCharacter::OnCameraBeginOverlap);
    CameraCollision->OnComponentEndOverlap.AddDynamic(this, &ASTUPlayerCharacter::OnCameraEndOverlap);
}

void ASTUPlayerCharacter::OnCameraBeginOverlap( UPrimitiveComponent* OverlappedComponent,
    AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    CheckCameraOverlap();
}

void ASTUPlayerCharacter::OnCameraEndOverlap(UPrimitiveComponent* OverlappedComponent,
    AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    CheckCameraOverlap();
}

void ASTUPlayerCharacter::CheckCameraOverlap() 
{
    const auto HideMesh = CameraCollision->IsOverlappingComponent(GetCapsuleComponent());
    GetMesh()->SetOwnerNoSee(HideMesh);

    TArray<USceneComponent*> AllChildrenMeshes;
    GetMesh()->GetChildrenComponents(true, AllChildrenMeshes);
    for (auto ChildMesh : AllChildrenMeshes)
    {
        const auto MeshChildGeometry = Cast<UPrimitiveComponent>(ChildMesh);
        if (MeshChildGeometry)
        {
            MeshChildGeometry->SetOwnerNoSee(HideMesh);
        }
    }
}
