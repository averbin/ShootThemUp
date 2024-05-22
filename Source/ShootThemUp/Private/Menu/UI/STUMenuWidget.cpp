// ShootThemUp Games. All rights reserved


#include "Menu/UI/STUMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void USTUMenuWidget::NativeOnInitialized() 
{
    Super::NativeOnInitialized();
    if (StartButton)
    {
        StartButton->OnClicked.AddDynamic(this, &USTUMenuWidget::OnStartButtonClicked);
    }
}

void USTUMenuWidget::OnStartButtonClicked() 
{
    const FName StartupLevelName = "TestMap";
    UGameplayStatics::OpenLevel(this, StartupLevelName);
}
