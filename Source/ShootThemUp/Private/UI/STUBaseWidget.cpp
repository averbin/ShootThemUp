// ShootThemUp Games. All rights reserved


#include "UI/STUBaseWidget.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

void USTUBaseWidget::Show() 
{
    if (!IsAnimationPlaying(ShowAnimation))
    {
        PlayAnimation(ShowAnimation);
        UGameplayStatics::PlaySound2D(GetWorld(), OpenSound);
    }
}
