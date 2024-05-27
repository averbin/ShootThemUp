// ShootThemUp Games. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "STUBaseCharacter.generated.h"


class USTUHealthComponent;
class USTUWeaponComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASTUBaseCharacter(const FObjectInitializer& ObjInit);

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USTUHealthComponent* HealthComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USTUWeaponComponent* WeaponComponent;

    UPROPERTY(EditDefaultsOnly, Category = "Animation")
    UAnimMontage* DeathAnimMontage;

    UPROPERTY(EditDefaultsOnly, Category = "Movement")
    FVector2D LandedDamageVelocity = FVector2D(900.0f, 1200.0f);

    UPROPERTY(EditDefaultsOnly, Category = "Movement")
    FVector2D LandedDamage = FVector2D(10.0f, 100.0f);

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Team")
    FLinearColor PlayerTeamColor;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Material")
    FName MaterialColorName = "Paint Color";

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    virtual void OnDeath();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    UFUNCTION(BlueprintCallable)
    virtual bool IsRunning() const;

    UFUNCTION(BlueprintCallable)
    float GetMovementDirection() const;

    void SetPlayerColor(const FLinearColor& NewColor);

protected:
    virtual void OnHealthChanged(float Health, float Delta);

private:
    UFUNCTION()
    void OnGroundLanded(const FHitResult& Hit);
};
