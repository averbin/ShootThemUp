#pragma once

class APawn;

class STUUtils
{
public:
    template <class T> 
    static T* GetSTUPlayerController(APawn* PlayerPawn) 
    {
        if (PlayerPawn)
        {
            if (const auto Component = PlayerPawn->GetComponentByClass(T::StaticClass()))
            {
                return Cast<T>(Component);
            }
        }

        return nullptr;
    }
};