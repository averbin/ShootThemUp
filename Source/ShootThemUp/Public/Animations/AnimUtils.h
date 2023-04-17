#pragma once

class UAnimSequenceBase;

class AnimUtils
{
public:
    template <class T> static T* FindNotifyByClass(UAnimSequenceBase* Animation)
    {
        if (!Animation)
            return nullptr;

        const auto NotifyEvents = Animation->Notifies;

        for (auto NotifyEvent : NotifyEvents)
        {
            if (auto AnimNotify = Cast<T>(NotifyEvent.Notify))
            {
                return AnimNotify;
            }
        }

        return nullptr;
    }
};