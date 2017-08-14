// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "BattleTank.h"
#include "Engine/World.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	// extract Z coordinate from Aim Direction
	// calculate angle of rotation (sinus)
	// Rotate the Barrel of the Angle Rotation given a max Elevation speed and the frametime
	
	auto ElevationChange = FMath::Clamp<float>(RelativeSpeed,-1,1) * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = FMath::Clamp(RelativeRotation.Pitch + ElevationChange, MinElevationDegrees, MaxElevationDegrees);
	SetRelativeRotation(FRotator(RawNewElevation, 0, 0));
	
}


