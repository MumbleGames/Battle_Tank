// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	if(!GetControlledTank())
	{	UE_LOG(LogTemp, Warning, TEXT("There is no Controlled Tank by the player")) }
	else
{
		FString TankName = GetControlledTank()->GetName();
		UE_LOG(LogTemp, Warning, TEXT("Controlled Tank by Player is %s"), *TankName) }
}

void ATankPlayerController::Tick(float Deltatime)
{
	Super::Tick(Deltatime);
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const

{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector OUTHitLocation; // OUT parameter
	if (GetSightRayHitLocation(OUTHitLocation)) // this is doing linetrace
	{
		UE_LOG(LogTemp, Warning, TEXT("Hitlocation : %s"), *OUTHitLocation.ToString())
			//TODO tell the controlled tank to aim at this point
	}
}

// Get world location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector &Location) const
{
	FCollisionQueryParams RV_TraceParams = FCollisionQueryParams(FName(TEXT("RV_Trace")), true, this);
	FHitResult RV_Hit(ForceInit);

	//cast a linetrace through the crosshair
	//if the linetrace intersects the world
		//put the location inside Location , and return true, else false
	Location = FVector(1.0);
	return false;
}


