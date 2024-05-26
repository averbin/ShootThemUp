// ShootThemUp Games. All rights reserved


#include "Menu/UI/STULevelItemWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void USTULevelItemWidget::NativeOnInitialized() 
{
    Super::NativeOnInitialized();

    if (LevelSelectButton)
    {
        LevelSelectButton->OnClicked.AddDynamic(this, &USTULevelItemWidget::OnLevelItemClicked);
    }
}

void USTULevelItemWidget::SetLevelData(const FLevelData& Data) 
{
    LevelData = Data;

    if (LevelNameTextBlock)
    {
        LevelNameTextBlock->Text = FText::FromName(LevelData.LevelName);
    }

    if (LevelImage)
    {
        LevelImage->SetBrushFromTexture(LevelData.LevelThumb);
    }
}

void USTULevelItemWidget::SetSelected(bool IsSelected) 
{
    if (FrameImage)
    {
        FrameImage->SetVisibility(IsSelected ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
    }
}

void USTULevelItemWidget::OnLevelItemClicked() 
{
    OnLevelSelected.Broadcast(LevelData);
}
