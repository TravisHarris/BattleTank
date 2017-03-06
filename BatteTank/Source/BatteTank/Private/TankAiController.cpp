// Fill out your copyright notice in the Description page of Project Settings.

#include "BatteTank.h"
#include "TankAiController.h"



void ATankAiController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();

	if (!ControlledTank) {
		UE_LOG(LogTemp, Error, TEXT("Ai Not Possessing Tank"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Ai Possesing %s"), *ControlledTank->GetName());
	}
	
}

ATank* ATankAiController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
