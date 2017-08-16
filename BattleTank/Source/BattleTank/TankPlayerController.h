// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // must be the last include

class ATank;

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public :
	
	void BeginPlay() override;
	void Tick(float Deltatime) override;

private :

	ATank* GetControlledTank() const;
	// move the barrel so that a shot would hit where the crosshair intersects the world
	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector& Location) const;

	bool GetLookDirection(FVector2D &ScreenLocation, FVector &WLocation, FVector &WDirection) const;
	bool GetLookVectorHitLocation(FVector &HitLocation, FVector Start, FVector AimDirection) const;

	UPROPERTY(EditDefaultsOnly)
		float CrossHairXLocation = 0.5;
	UPROPERTY(EditDefaultsOnly)
		float CrossHairYLocation = 0.33333;
	UPROPERTY(EditDefaultsOnly)
		float LineTraceRange = 1000000;

};
