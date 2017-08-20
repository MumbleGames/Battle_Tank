// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAiController.h"
#include "Tank.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
//Depends on MovementComponent via Pathfinding system

void ATankAiController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAiController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto AITank = Cast<ATank>(GetPawn());
	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (ensure(PlayerTank))
	{
		MoveToActor(PlayerTank, AcceptanceRadius);
		AITank->AimAt(PlayerTank->GetActorLocation());
		AITank->Fire(); 
	}
}