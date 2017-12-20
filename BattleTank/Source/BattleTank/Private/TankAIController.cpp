// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "Tank.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();

}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	auto PlayerTank = Cast<ATank> (GetWorld()->GetFirstPlayerController()->GetPawn());

	auto AItank = Cast<ATank>(GetPawn());

	if (PlayerTank)
	{
		// TODO Move towards the player


		// Aim towards the player
		AItank->AimAt(PlayerTank->GetTargetLocation());

		// TODO limit firing rate
		AItank->Fire();

	}
	else 
	{
		return;
	}
	
}