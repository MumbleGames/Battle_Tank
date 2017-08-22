// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::BeginPlay()
{
	//So that first fire is after initial Reload
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::Initialise(UTankTurret * TurretToSet, UTankBarrel * BarrelToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	if (Ammo == 0) AimingStatus = EFiringStatus::OutOfAmmo;
	else {
		if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
			AimingStatus = EFiringStatus::Reloading;
		else if (IsBarrelMoving())
			AimingStatus = EFiringStatus::Aiming;
		else  AimingStatus = EFiringStatus::Locked;
		}
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) return false;
	auto BarrelForward = Barrel->GetForwardVector();
	return !BarrelForward.Equals(AimDirection, 0.01);
}

void UTankAimingComponent::AimLogging(FVector AimLocation)
{
	if (!ensure(Barrel)) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	// calculate the OutLaunchVelocity
	
	if (UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, AimLocation, LaunchSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace))
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrel(AimDirection);
		MoveTurret(AimDirection);

		auto Time = GetWorld()->GetTimeSeconds();
		
	}
	else
	{
		auto Time = GetWorld()->GetTimeSeconds();
	}
}

EFiringStatus UTankAimingComponent::GetAimingStatus() const
{
	return AimingStatus;
}

void UTankAimingComponent::MoveBarrel(FVector DirectionVector)
{
	if (!ensure(Barrel)) { return; }
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimRotator = DirectionVector.Rotation();
	auto DeltaRotator = AimRotator - BarrelRotator;
	
		Barrel->Elevate(DeltaRotator.Pitch);
}

void UTankAimingComponent::MoveTurret(FVector DirectionVector)
{
	if (!ensure(Turret)) { return; }
	auto TurretRotator = Turret->GetForwardVector().Rotation();
	auto AimRotator = DirectionVector.Rotation();
	auto DeltaRotator = AimRotator - TurretRotator;
	if (FMath::Abs<float>(DeltaRotator.Yaw) > 180.0) DeltaRotator.Yaw = -DeltaRotator.Yaw;
	Turret->Turn(DeltaRotator.Yaw);
}

void UTankAimingComponent::Fire()
{
	if (AimingStatus==EFiringStatus::Aiming || AimingStatus==EFiringStatus::Locked)
	{
		if (!ensure(Barrel)) return;
		if (!ensure(ProjectileBlueprint)) return;
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation(FName("Projectile")), Barrel->GetSocketRotation(FName("Projectile")));
		if (ensure(Projectile))
		{
			Projectile->LaunchProjectile(LaunchSpeed);
			LastFireTime = FPlatformTime::Seconds();
			DecreaseAmmo();
			
		}
	}
}

void UTankAimingComponent::DecreaseAmmo()
{
	Ammo = FMath::Clamp<int32>(Ammo - 1,0,3); 
}