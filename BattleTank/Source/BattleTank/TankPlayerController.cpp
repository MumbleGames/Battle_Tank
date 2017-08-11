// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"



void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	if(!GetControlledTank())
	{	UE_LOG(LogTemp, Warning, TEXT("There is no Controlled Tank by the player")) }
	else
{
		FString TankName = GetControlledTank()->GetName();
		UE_LOG(LogTemp, Warning, TEXT("Controlled Tank is %s"), *TankName) }
}

ATank* ATankPlayerController::GetControlledTank() const

{
	return Cast<ATank>(GetPawn());
}


