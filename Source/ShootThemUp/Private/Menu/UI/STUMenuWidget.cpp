// ShootThemUp Games. All rights reserved


#include "Menu/UI/STUMenuWidget.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Kismet/GameplayStatics.h"
#include "STUGameInstance.h"
#include "Menu/UI/STULevelItemWidget.h"

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

    InitLevelItems();
}

void USTUMenuWidget::OnStartButtonClicked() 
{
    const auto STUGameInstance = GetSTUGameInstance();
    if (!STUGameInstance)
        return;

    UGameplayStatics::OpenLevel(this, STUGameInstance->GetStartupLevel().LevelName);
}

void USTUMenuWidget::OnQuitGameButtonClicked() 
{
    UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}

void USTUMenuWidget::OnLevelSelected(const FLevelData& Data) 
{
    const auto GameInstance = GetSTUGameInstance();
    if (!GameInstance)
        return;
    GameInstance->SetStartupLevel(Data);

    for (auto LevelItemWidget : LevelItemWidgets)
    {
        if (LevelItemWidget)
        {
            const auto IsSelected = LevelItemWidget->GetLevelData().LevelName == Data.LevelName;
            LevelItemWidget->SetSelected(IsSelected);
        }
    }
}

void USTUMenuWidget::InitLevelItems() 
{
    const auto GameInstance = GetSTUGameInstance();
    if (!GameInstance)
        return;
    checkf(GameInstance->GetLevelsData().Num() != 0, TEXT("Level data must not be empty"));

    if (!LevelItemsBox)
        return;

    LevelItemsBox->ClearChildren();

    for (auto LevelData : GameInstance->GetLevelsData())
    {
        const auto LevelItemWidget = CreateWidget<USTULevelItemWidget>(GetWorld(), LevelItemWidgetClass);
        if (!LevelItemWidget)
            continue;
        LevelItemWidget->SetLevelData(LevelData);
        LevelItemWidget->OnLevelSelected.AddUObject(this, &USTUMenuWidget::OnLevelSelected);

        LevelItemsBox->AddChild(LevelItemWidget);
        LevelItemWidgets.Add(LevelItemWidget);
    }

    if (GameInstance->GetStartupLevel().LevelName.IsNone())
    {
        OnLevelSelected(GameInstance->GetLevelsData()[0]);
    }
    else
    {
        OnLevelSelected(GameInstance->GetStartupLevel());
    }
}

USTUGameInstance* USTUMenuWidget::GetSTUGameInstance() const
{
    if (!GetWorld())
        return nullptr;

    return GetWorld()->GetGameInstance<USTUGameInstance>();
}
