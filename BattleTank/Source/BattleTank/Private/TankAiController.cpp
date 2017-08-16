// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAiController.h"
#include "Tank.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"

void ATankAiController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAiController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto AITank = Cast<ATank>(GetPawn());
	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	//TODO Move Towards the player

	// Aim towards the player
	if (PlayerTank)
	{
		AITank->AimAt(PlayerTank->GetActorLocation());
		AITank->Fire(); // TODO limit Fire Rate
	}
}