// ShootThemUp Games. All rights reserved


#include "Menu/UI/STUMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "STUGameInstance.h"

DEFINE_LOG_CATEGORY_STATIC(LogUSTUMenuWidget, All, All)

void USTUMenuWidget::NativeOnInitialized() 
{
    Super::NativeOnInitialized();

    if (StartButton)
    {
        StartButton->OnClicked.AddDynamic(this, &USTUMenuWidget::OnStartButtonClicked);
    }

    if (QuitGameButton)
    {
        QuitGameButton->OnClicked.AddDynamic(this, &USTUMenuWidget::OnQuitGameButtonClicked);
    }
}

void USTUMenuWidget::OnStartButtonClicked() 
{
    if (!GetWorld())
        return;

    const auto STUGameInstance = GetWorld()->GetGameInstance<USTUGameInstance>();
    if (!STUGameInstance)
        return;

    if (STUGameInstance->GetStartupLevelName().IsNone())
    {
        UE_LOG(LogUSTUMenuWidget, Error, TEXT("StartupLevelName is empty!"))
        return;
    }

    UGameplayStatics::OpenLevel(this, STUGameInstance->GetStartupLevelName());
}

void USTUMenuWidget::OnQuitGameButtonClicked() 
{
    UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}
