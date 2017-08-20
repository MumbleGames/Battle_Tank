// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Tank.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime,TickType,ThisTickFunction);
	// calculer la vitesse de glissage
	auto SlippageSpeed = FVector::DotProduct(ComponentVelocity, GetRightVector());

	UE_LOG(LogTemp, Warning, TEXT("tank : %s ticking bitch :"), *GetName())

		// trouver l'accélération à appliquer pour la compenser
		auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();
	// calculer et appliquer la force à appliquer ( F = m a)
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = TankRoot->GetMass()*CorrectionAcceleration/2;
	TankRoot->AddForce(CorrectionForce);
}
void UTankTrack::SetThrottle(float Throttle)
{
		//TODO Clamp Throttle Value so the Axis Sensitivity doesn't accelerate the Throttle
		auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
		auto ForceLocation = GetComponentLocation();
		auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
		TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

