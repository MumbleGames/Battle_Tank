// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAiController.h"

void ATankAiController::BeginPlay()
{
	Super::BeginPlay();
	auto PlayerTank = GetPlayerTank();
	UE_LOG(LogTemp, Warning, TEXT("Le tank du joueur que l'IA detecte est %s"), *PlayerTank->GetName() )
	if (!GetControlledTank())
	{
		UE_LOG(LogTemp, Warning, TEXT("L'IA ne controlle pas de tank"))
	}
}

ATank* ATankAiController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAiController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Tank introuvable par l'IA"))
			return nullptr;
	}
	else
	{
		return Cast<ATank>(PlayerPawn);
	}
}
