#pragma once

class AActor;

class STUUtils
{
public:
    template <class T> 
    static T* GetSTUPlayerController(AActor* PlayerActor) 
    {
        if (PlayerActor)
        {
            if (const auto Component = PlayerActor->GetComponentByClass(T::StaticClass()))
            {
                return Cast<T>(Component);
            }
        }

        return nullptr;
    }
};