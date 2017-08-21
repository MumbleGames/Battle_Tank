// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "TankAimingComponent.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	
	FoundAimingComponent(AimingComponent);
	
}

void ATankPlayerController::Tick(float Deltatime)
{
	Super::Tick(Deltatime);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetPawn()) return;
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }

	FVector OUTHitLocation; // OUT parameter
	if (GetSightRayHitLocation(OUTHitLocation)) // this is doing linetrace
	{
		AimingComponent->AimLogging(OUTHitLocation);
	}

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



