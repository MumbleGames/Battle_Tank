// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAiController.generated.h"

class ABattleTankGameModeBase;

UCLASS()
class BATTLETANK_API ATankAiController : public AAIController
{
	GENERATED_BODY()
	
public: 

	void BeginPlay() override;
	void Tick(float DeltaTime) override;
	
	UFUNCTION()
		void OnTankDeath();
	UFUNCTION(BlueprintImplementableEvent)
		void EnnemyDown();

protected :

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float AcceptanceRadius = 8000;
	UFUNCTION(BlueprintCallable, Category = "Setup")
		void SettingGameMode(ABattleTankGameModeBase* GameModeToSet);

private:

	virtual void SetPawn(APawn* InPawn) override;
	ABattleTankGameModeBase* GameMode;
};
