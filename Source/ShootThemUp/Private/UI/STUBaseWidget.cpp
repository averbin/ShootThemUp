// ShootThemUp Games. All rights reserved


#include "UI/STUBaseWidget.h"

void USTUBaseWidget::Show() 
{
    if (!IsAnimationPlaying(ShowAnimation))
    {
        PlayAnimation(ShowAnimation);
    }
}
