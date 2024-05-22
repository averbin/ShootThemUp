// ShootThemUp Games. All rights reserved


#include "UI/STUMainMenuWidget.h"
#include "Components/Button.h"
#include "STUGameInstance.h"
#include "Kismet/GameplayStatics.h"

void USTUMainMenuWidget::NativeOnInitialized() 
{
    Super::NativeOnInitialized();

    if (GameMenuButton)
    {
        GameMenuButton->OnClicked.AddDynamic(this, &USTUMainMenuWidget::OnGameMenuButtonClicked);
    }
}

void USTUMainMenuWidget::OnGameMenuButtonClicked() 
{
    if (!GetWorld() || !GetWorld()->GetGameInstance<USTUGameInstance>())
        return;
    UGameplayStatics::OpenLevel(this, GetWorld()->GetGameInstance<USTUGameInstance>()->GetMainMenuLevelName());
}
