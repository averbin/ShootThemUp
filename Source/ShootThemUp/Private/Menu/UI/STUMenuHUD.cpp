// ShootThemUp Games. All rights reserved


#include "Menu/UI/STUMenuHUD.h"
#include "STUBaseWidget.h"

void ASTUMenuHUD::BeginPlay() 
{
    Super::BeginPlay();

    if (MenuWidgetClass)
    {
        const auto MenuWidget = CreateWidget<USTUBaseWidget>(GetWorld(), MenuWidgetClass);
        if (MenuWidget)
        {
            MenuWidget->AddToViewport();
            MenuWidget->Show();
        }
    }
}
