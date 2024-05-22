// ShootThemUp Games. All rights reserved


#include "Menu/STUMenuPlayerController.h"
#include "STUGameInstance.h"

void ASTUMenuPlayerController::BeginPlay()
{
    Super::BeginPlay();

    SetInputMode(FInputModeUIOnly());

    bShowMouseCursor = true;

    GetWorld()->GetGameInstance<USTUGameInstance>()->TestString = "Controller";
}
