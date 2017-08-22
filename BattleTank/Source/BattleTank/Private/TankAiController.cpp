// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAiController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
//Depends on MovementComponent via Pathfinding system

void ATankAiController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAiController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	auto AITank = GetPawn();
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (ensure(PlayerTank))
	{
		MoveToActor(PlayerTank, AcceptanceRadius);
		AimingComponent->AimLogging(PlayerTank->GetActorLocation()); 

		if(AimingComponent->GetAimingStatus()== EFiringStatus::Locked)
		AimingComponent->Fire(); 
	}
}