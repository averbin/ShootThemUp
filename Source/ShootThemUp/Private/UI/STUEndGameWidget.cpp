// ShootThemUp Games. All rights reserved


#include "UI/STUEndGameWidget.h"
#include "../STUGameModeBase.h"
#include "Player/STUPlayerState.h"
#include "UI/STUPlayerStatsRowWidget.h"
#include "Components/VerticalBox.h"
#include "Components/Button.h"
#include "STUUtils.h"
#include "Kismet/GameplayStatics.h"

void USTUEndGameWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (GetWorld())
    {
        const auto GameMode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());
        if (!GameMode)
            return;
        GameMode->OnMatchStateChanged.AddUObject(this, &USTUEndGameWidget::OnMatchStateChanged);
    }

    if (ResetLevelButton)
    {
        ResetLevelButton->OnClicked.AddDynamic(this, &USTUEndGameWidget::OnResetLevel);
    }
}

void USTUEndGameWidget::OnMatchStateChanged(ESTUMatchState State)
{
    if (State == ESTUMatchState::EndGame)
    {
        UpdatePlayerStat();
    }
}

void USTUEndGameWidget::UpdatePlayerStat() 
{
    if (!GetWorld() || !PlayerStatBox)
        return;

    PlayerStatBox->ClearChildren();

    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        const auto Controller = It->Get();
        if (!Controller)
            continue;
        const auto PlayerState = Cast<ASTUPlayerState>(Controller->PlayerState);
        if (!PlayerState)
            continue;

        const auto PlayerStatWidget = CreateWidget<USTUPlayerStatsRowWidget>(GetWorld(), PlayerStatWidgetClass);
        if (!PlayerStatWidget)
            continue;

        PlayerStatWidget->SetPlayerName(FText::FromString(PlayerState->GetPlayerName()));
        PlayerStatWidget->SetKills(STUUtils::TextFromInt(PlayerState->GetKills()));
        PlayerStatWidget->SetDeaths(STUUtils::TextFromInt(PlayerState->GetDeaths()));
        PlayerStatWidget->SetTeam(STUUtils::TextFromInt(PlayerState->GetTeamID()));
        PlayerStatWidget->SetPlayerIndicator(Controller->IsPlayerController());
        PlayerStatWidget->SetTeamColor(PlayerState->GetTeamColor());

        PlayerStatBox->AddChild(PlayerStatWidget);
    }
}

void USTUEndGameWidget::OnResetLevel() 
{
    const FName LoadLevelName = "TestLevel";
    const FString CurrentLevel = UGameplayStatics::GetCurrentLevelName(this);
    UGameplayStatics::OpenLevel(this, FName(CurrentLevel));
}
