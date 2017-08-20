// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAiController.generated.h"


class ATank;

UCLASS()
class BATTLETANK_API ATankAiController : public AAIController
{
	GENERATED_BODY()
	
public: 

	void BeginPlay() override;
	void Tick(float DeltaTime) override;

private:
	// tells how close the AI can get before firing.
	float AcceptanceRadius = 5000;
	
};
