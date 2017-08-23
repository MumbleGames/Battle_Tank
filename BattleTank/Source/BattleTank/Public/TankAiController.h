// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAiController.generated.h"


UCLASS()
class BATTLETANK_API ATankAiController : public AAIController
{
	GENERATED_BODY()
	
public: 

	void BeginPlay() override;
	void Tick(float DeltaTime) override;
	
	UFUNCTION()
		void OnTankDeath();

protected :

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float AcceptanceRadius = 8000;

private:

	virtual void SetPawn(APawn* InPawn) override;
	
};
