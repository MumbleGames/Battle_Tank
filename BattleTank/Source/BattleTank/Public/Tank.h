// Fill out your copyright notice in the Description page of Project Settings.
//DONE : créer des images et des boutons pour les widget de victoire et de défaite

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

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

	FTankDelegate OnDeath;

	virtual void BeginPlay() override;

private:
	// Sets default values for this pawn's properties
	ATank();
	UPROPERTY(EditAnywhere, Category = "Setup")
		int32 MaxHealth = 400;
	UPROPERTY(VisibleAnywhere, Category = "Setup")
		int32 CurrentHealth = MaxHealth;
	
};

