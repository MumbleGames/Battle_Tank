// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Forward Declaration
class UTankBarrel; //Holds barrel's properties
class UTankTurret; // Holds Turret Property

UENUM()
enum class EFiringStatus : uint8 { Reloading, Aiming, Locked};
/**
* Responsible for aiming the tank's fires
*/
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankTurret* TurretToSet, UTankBarrel* BarrelToSet);

	void AimLogging(FVector AimLocation);
	
		

protected :

	UPROPERTY(BlueprintReadOnly, Category = "State")
		EFiringStatus AimingStatus = EFiringStatus::Aiming;

private:
	// Sets default values for this component's properties
	UTankAimingComponent();

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LaunchSpeed = 8000;

	void MoveBarrel(FVector DirectionVector);

	void MoveTurret(FVector DirectionVector);
	
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
};
