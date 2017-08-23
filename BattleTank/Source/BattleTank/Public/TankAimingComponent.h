// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Forward Declaration
class UTankBarrel; //Holds barrel's properties
class UTankTurret; // Holds Turret Property
class AProjectile;

UENUM()
enum class EFiringStatus : uint8 { Reloading, Aiming, Locked, OutOfAmmo};
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

	UFUNCTION(BlueprintCallable)
		void Fire();

	UFUNCTION(BlueprintCallable)
	void DecreaseAmmo();
	
	void AimLogging(FVector AimLocation);
	
	EFiringStatus GetAimingStatus() const;
	
protected :

	UPROPERTY(BlueprintReadOnly, Category = "State")
		EFiringStatus AimingStatus = EFiringStatus::Aiming;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Firing")
		int32 Ammo;

private:
	// Sets default values for this component's properties
	UTankAimingComponent();

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LaunchSpeed = 8000;
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float ReloadTimeInSeconds = 3;
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		TSubclassOf<AProjectile> ProjectileBlueprint;	 // Alternative
	
	bool IsBarrelMoving();

	void MoveBarrel(FVector DirectionVector);

	void MoveTurret(FVector DirectionVector);
	
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
	
	FVector AimDirection;
	double LastFireTime = 0;
};
