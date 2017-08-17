// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"





void UTankTrack::SetThrottle(float Throttle)
{
	auto Name = GetName();
	

		//Clamp Throttle Value so the Axis Sensitivity doesn't accelerate the Throttle

		auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
		auto ForceLocation = GetComponentLocation();
		UE_LOG(LogTemp, Warning, TEXT("%s : Location is  is %s"), *Name, *ForceLocation.ToString())
		auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
		TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);

}

