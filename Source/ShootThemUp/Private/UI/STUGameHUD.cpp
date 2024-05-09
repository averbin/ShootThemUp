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
    if (auto PlayerHUDWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass))
    {
        PlayerHUDWidget->AddToViewport();
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
    UE_LOG(LogASTUGameHUD, Display, TEXT("_-_-_ Match State: %s"), *UEnum::GetValueAsString(MatchState));
}
