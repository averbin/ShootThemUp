// ShootThemUp Games. All rights reserved


#include "Menu/STUMenuPlayerController.h"

void ASTUMenuPlayerController::BeginPlay()
{
    Super::BeginPlay();

    SetInputMode(FInputModeUIOnly());

    bShowMouseCursor = true;
}
