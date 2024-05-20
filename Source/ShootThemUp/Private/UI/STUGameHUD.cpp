// ShootThemUp Games. All rights reserved


#include "UI/STUGameHUD.h"
#include "Engine/Canvas.h"
#include "Blueprint/UserWidget.h"
#include "../STUGameModeBase.h"

DEFINE_LOG_CATEGORY_STATIC(LogASTUGameHUD, Display, Display);

void ASTUGameHUD::DrawHUD() 
{
    Super::DrawHUD();

    //DrawCrossHair();
} 

void ASTUGameHUD::BeginPlay() 
{
    Super::BeginPlay();

    GameWidgets.Add(ESTUMatchState::InProgress, CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass));
    GameWidgets.Add(ESTUMatchState::Pause, CreateWidget<UUserWidget>(GetWorld(), PauseWidgetClass));
    GameWidgets.Add(ESTUMatchState::EndGame, CreateWidget<UUserWidget>(GetWorld(), EndGameWidgetClass));

    for (auto WidgetPair : GameWidgets)
    {
        const auto Widget = WidgetPair.Value;
        if (!Widget)
            continue;
        Widget->AddToViewport();
        Widget->SetVisibility(ESlateVisibility::Hidden);
    }

    if (GetWorld())
    {
        const auto GameMode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());
        if (!GameMode)
            return;
        GameMode->OnMatchStateChanged.AddUObject(this, &ASTUGameHUD::OnMatchStateChanged);
    }
}

void ASTUGameHUD::DrawCrossHair()
{
    const TInterval<float> Center(Canvas->SizeX * 0.5f, Canvas->SizeY * 0.5f);

    const float HalfLineSize = 10.0f;
    const float LineThikness = 2.0f;
    const FLinearColor LineColor = FLinearColor::Green;

    DrawLine(Center.Min - HalfLineSize, Center.Max, Center.Min + HalfLineSize, Center.Max, LineColor, LineThikness);
    DrawLine(Center.Min, Center.Max - HalfLineSize, Center.Min, Center.Max + HalfLineSize, LineColor, LineThikness);
}

void ASTUGameHUD::OnMatchStateChanged(ESTUMatchState MatchState) 
{
    if (CurrentWidget)
    {
        CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
    }

    if (GameWidgets[MatchState])
    {
        CurrentWidget = GameWidgets[MatchState];
        CurrentWidget->SetVisibility(ESlateVisibility::Visible);
    }
    UE_LOG(LogASTUGameHUD, Display, TEXT("_-_-_ Match State: %s"), *UEnum::GetValueAsString(MatchState));
}
