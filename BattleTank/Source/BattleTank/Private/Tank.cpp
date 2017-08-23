// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

//On prend des damages : trouver le projectile qui m'a touch�
//grace � cette information, appeler TakeDamage
// Retirer des HP en fonction de ce que TakeDamage retourne

float ATank::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	int32 DamagePoints = FMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp(DamagePoints, 0, CurrentHealth);
		CurrentHealth -= DamageToApply;
		if(CurrentHealth <=0)
		{   }
	return DamageToApply;
}
