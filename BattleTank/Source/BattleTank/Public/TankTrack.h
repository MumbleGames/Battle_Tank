// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * TankTrack is used to set a maximum driving force, and to apply forces to the tank.
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public :
	// Set a throttle between -1 and +1
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float throttle);
	
	//Max force per Track in Newton
	UPROPERTY(EditDefaultsOnly)
		float TrackMaxDrivingForce = 1500000;
private :
	UTankTrack();
	//Delegate Declaration : On Hit est appelé dès que le track est "hit" par qqch
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	virtual void BeginPlay() override;
	
	void ApplySideForce();

	void DriveTrack();

	float CurrentThrottle = 0;

 };
