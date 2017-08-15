// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Tank.h"

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

ATank* ATankPlayerController::GetControlledTank() const

{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::Tick(float Deltatime)
{
	Super::Tick(Deltatime);
	AimTowardsCrosshair();
}


void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector OUTHitLocation; // OUT parameter
	if (GetSightRayHitLocation(OUTHitLocation)) // this is doing linetrace
	{
		GetControlledTank()->AimAt(OUTHitLocation);
	}
	else {UE_LOG(LogTemp,Warning, TEXT("%f : Can't See Aim-Target"), GetWorld()->GetTimeSeconds()) }

}

// Get world location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector &Location) const
{

	//find crosshair position
	int32 ViewPortSize_x, ViewPortSize_y;
	GetViewportSize(ViewPortSize_x, ViewPortSize_y);
	auto ScreenLocation = FVector2D(ViewPortSize_x*CrossHairXLocation, ViewPortSize_y*CrossHairYLocation);
	

	// De-project the screen position of the crosshair to a world direction
	FVector OUTLookDirection, OUTLookLocation;
	if(GetLookDirection(ScreenLocation, OUTLookLocation, OUTLookDirection))
	{
		return GetLookVectorHitLocation(Location, OUTLookLocation, OUTLookDirection);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Unable to find AimDirection and AimLocation"))
			return false;
		}
		// linetrace along that look LookDirection and see what we hit (up to max range)
		
	
}

bool ATankPlayerController::GetLookDirection(FVector2D &ScreenLocation, FVector &WLocation, FVector &WDirection) const
{
	
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WLocation, WDirection);
	
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector & HitLocation,FVector Start, FVector AimDirection) const
{
	FHitResult Hit;
	FVector End = Start + AimDirection*LineTraceRange;
	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECollisionChannel::ECC_Visibility))
	{
		HitLocation = Hit.Location;
		return true;
	}
	HitLocation = FVector(0);
	return false;
}



