// ShootThemUp Games. All rights reserved


#include "Player/STUPlayerController.h"
#include "Components/STURespawnComponent.h"
#include "../STUGameModeBase.h"

ASTUPlayerController::ASTUPlayerController() 
{
    RespawnComponent = CreateDefaultSubobject<USTURespawnComponent>("USTURespawnComponent");
}

void ASTUPlayerController::BeginPlay() 
{
    Super::BeginPlay();

    if (GetWorld())
    {
        const auto GameMode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());
        if (GameMode)
        {
            GameMode->OnMatchStateChanged.AddUObject(this, &ASTUPlayerController::OnMatchStateChanged);
        }
    }
}

void ASTUPlayerController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    OnNewPawn.Broadcast(InPawn);
}

void ASTUPlayerController::SetupInputComponent() 
{
    Super::SetupInputComponent();

    if (!InputComponent)
        return;

    InputComponent->BindAction("PauseGame", EInputEvent::IE_Pressed, this, &ASTUPlayerController::OnPauseGame);
}

void ASTUPlayerController::OnPauseGame() 
{
    if (!GetWorld() || !GetWorld()->GetAuthGameMode())
        return;

    const auto GameMode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());
    if (!GameMode)
        return;
    GameMode->SetPause(this);
}

void ASTUPlayerController::OnMatchStateChanged(ESTUMatchState State)
{
    bShowMouseCursor = (State != ESTUMatchState::InProgress);
    if (bShowMouseCursor)
        SetInputMode(FInputModeUIOnly());
    else
        SetInputMode(FInputModeGameOnly());
}
