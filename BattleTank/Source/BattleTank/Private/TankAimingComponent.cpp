// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent* BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation("Projectile");
	bool hasAimSolution = UGameplayStatics::SuggestProjectileVelocity(
							this,
							OutLaunchVelocity,
							StartLocation,
							HitLocation,
							LaunchSpeed,
							ESuggestProjVelocityTraceOption::DoNotTrace);

	if (hasAimSolution) {
		FVector AimDirection = OutLaunchVelocity.GetSafeNormal();
		FString TankName = GetOwner()->GetName();
		MoveBarrelTowards(AimDirection);
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	// Work-out difference between current barrel rotation and AimDirection
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator AimRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimRotator - BarrelRotator;

	UE_LOG(LogTemp, Warning, TEXT("AimRotator: %s"), *AimRotator.ToString());
	UE_LOG(LogTemp, Warning, TEXT("BarrelRotator: %s"), *BarrelRotator.ToString());

	// Move the barrel the right amount this frame
	// Given a max elevation speed and frame time
}