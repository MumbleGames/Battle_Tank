// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"


UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:	
	//called by ApplyRadialDamage (sur projectile.cpp)
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
		
	//returns current health as a % of MaxHealth
	UFUNCTION(BlueprintPure, Category="Health")
	float GetHealthPercent() const;
private:
	// Sets default values for this pawn's properties
	ATank();
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		int32 MaxHealth = 100;
	UPROPERTY(VisibleAnywhere, Category = "Setup")
		int32 CurrentHealth = MaxHealth;

	
};
