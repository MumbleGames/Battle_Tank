// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAiController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "Tank.h"
#include "BattleTankGameModeBase.h"
//Depends on MovementComponent via Pathfinding system

void ATankAiController::BeginPlay()
{
	Super::BeginPlay();
		if (GetPawn()->GetClass()->IsChildOf(ATank::StaticClass()))
		{
			if (!ensure(GameMode)) { return; }
			GameMode->EnnemyCount += 1;
		}
}

void ATankAiController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	auto AITank = GetPawn();
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (PlayerTank)
	{	//Appelle RequestDirectMove dans TankMovementComponent
		MoveToActor(PlayerTank, AcceptanceRadius);
		AimingComponent->AimLogging(PlayerTank->GetActorLocation()); 

		if(AimingComponent->GetAimingStatus()== EFiringStatus::Locked)
		AimingComponent->Fire(); 
	}
}

void ATankAiController::OnTankDeath()
{
	if (!GetPawn()) return;
	if (GetPawn()->GetClass()->IsChildOf(ATank::StaticClass()))
	{
		if (!ensure(GameMode)) { return; }
		GameMode->EnnemyCount -= 1;
		EnnemyDown();
	}
	GetPawn()->DetachFromControllerPendingDestroy();
}

void ATankAiController::SettingGameMode(ABattleTankGameModeBase * GameModeToSet)
{
	GameMode = GameModeToSet;
}

void ATankAiController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!(PossessedTank)) return;
		
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAiController::OnTankDeath);
		//subscribe our local method to the Tank's Death event.
	}
}
