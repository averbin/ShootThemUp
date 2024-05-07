// ShootThemUp Games. All rights reserved


#include "STUGameModeBase.h"
#include "Player/STUBaseCharacter.h"
#include "Player/STUPlayerController.h"
#include "UI/STUGameHUD.h"
#include "AIController.h"
#include "Player/STUPlayerState.h"
#include "STUUtils.h"
#include "Components/STURespawnComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogASTUGameModeBase, All, All);

constexpr static int32 MinRoundTimeForRespawn = 10;

ASTUGameModeBase::ASTUGameModeBase() 
{
    DefaultPawnClass = ASTUBaseCharacter::StaticClass();
    PlayerControllerClass = ASTUPlayerController::StaticClass();
    HUDClass = ASTUGameHUD::StaticClass();
    PlayerStateClass = ASTUPlayerState::StaticClass();
}

void ASTUGameModeBase::StartPlay()
{
    Super::StartPlay();

    SpawnBots();
    CreateTeamsInfo();

    CurrentRound = 1;
    StartRound();
}

UClass* ASTUGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
    if (InController && InController->IsA<AAIController>())
    {
        return AIPawnClass;
    }

    return Super::GetDefaultPawnClassForController_Implementation(InController);
}

void ASTUGameModeBase::Killed(AController* KillerController, AController* VictimController) 
{
    if (!KillerController || !VictimController)
        return;
    if (const auto KillerPlayerState = Cast<ASTUPlayerState>(KillerController->PlayerState))
        KillerPlayerState->AddKills();
    if (const auto VictomPlayerState = Cast<ASTUPlayerState>(VictimController->PlayerState))
        VictomPlayerState->AddDeaths();

    StartRespawn(VictimController);
}

void ASTUGameModeBase::RespawnRequest(AController* Controller) 
{
    ResetOnePlayer(Controller);
}

void ASTUGameModeBase::SpawnBots()
{
    if (!GetWorld())
        return;

    for (auto i = 0; i != GameData.PlayersNum - 1; ++i)
    {
        FActorSpawnParameters SpawnInfo;
        SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
        const auto STUAIController = GetWorld()->SpawnActor<AAIController>(AIControllerClass,SpawnInfo);
        RestartPlayer(STUAIController);
    }
}

void ASTUGameModeBase::StartRound()
{
    RoundCountDown = GameData.RoundTime;
    GetWorldTimerManager().SetTimer(GameRoundTimerHandle, this, &ASTUGameModeBase::GameTimerUpdate, 1.0f, true);
}

void ASTUGameModeBase::StartRespawn(AController* Controller) 
{
    const auto IsRespawnAvailable = RoundCountDown > MinRoundTimeForRespawn;
    if (!IsRespawnAvailable)
        return;

    const auto RespawnComponent = STUUtils::GetSTUPlayerController<USTURespawnComponent>(Controller);
    if (!RespawnComponent)
        return;
    RespawnComponent->Respawn(GameData.RespawnTime);
}

void ASTUGameModeBase::GameTimerUpdate() 
{
    UE_LOG(LogASTUGameModeBase, Display, TEXT("_-_-_: Time: %i, Round: %i/%i _-_-_"), RoundCountDown, CurrentRound, GameData.Rounds);
    if (--RoundCountDown == 0)
    {
        GetWorldTimerManager().ClearTimer(GameRoundTimerHandle);
        if (CurrentRound + 1 <= GameData.Rounds)
        {
            ++CurrentRound;
            ResetPlayers();
            StartRound();
        }
        else
        {
            LogPlayersInfo();
            UE_LOG(LogASTUGameModeBase, Display, TEXT("_-_-_: Game Over _-_-_"));
        }
    }
}

void ASTUGameModeBase::ResetPlayers() 
{
    if (!GetWorld())
        return;
    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        ResetOnePlayer(It->Get());
    }
}

void ASTUGameModeBase::ResetOnePlayer(AController* Controller)
{
    if (Controller && Controller->GetPawn())
    {
        Controller->GetPawn()->Reset();
    }
    RestartPlayer(Controller);
    SetPlayerColor(Controller);
}

void ASTUGameModeBase::CreateTeamsInfo()
{
    if (!GetWorld())
        return;

    int32 TeamID = 1;
    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        const auto Controller = It->Get();
        if (!Controller)
            continue;
        const auto PlayerState = Cast<ASTUPlayerState>(Controller->GetPawn()->GetPlayerState());
        if (!PlayerState)
            continue;

        PlayerState->SetTeamID(TeamID);
        PlayerState->SetTeamColor(DetermineColorByTeamID(TeamID));
        SetPlayerColor(Controller);
        TeamID = TeamID == 1 ? 2 : 1;
    }
}

FLinearColor ASTUGameModeBase::DetermineColorByTeamID(const int32 TeamID) const
{
    if (TeamID - 1 < GameData.TeamColors.Num())
    {
        return GameData.TeamColors[TeamID - 1];
    }
    return GameData.DefaultTeamColor;
}

void ASTUGameModeBase::SetPlayerColor(AController* Controller) 
{
    if (!Controller)
        return;

    const auto Character = Cast<ASTUBaseCharacter>(Controller->GetPawn());
    if (!Character)
        return;

    const auto PlayerState = Cast<ASTUPlayerState>(Character->GetPlayerState());
    if (!PlayerState)
        return;
    Character->SetPlayerColor(PlayerState->GetTeamColor());
}

void ASTUGameModeBase::LogPlayersInfo() 
{
    if (!GetWorld())
        return;

    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        const auto Controller = It->Get();
        if (!Controller)
            continue;
        const auto PlayerState = Cast<ASTUPlayerState>(Controller->GetPawn()->GetPlayerState());
        if (!PlayerState)
            continue;

        PlayerState->LogInfo();
    }
 }
