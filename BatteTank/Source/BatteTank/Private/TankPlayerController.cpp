// Fill out your copyright notice in the Description page of Project Settings.

#include "BatteTank.h"
#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();

	if (!ControlledTank) {
		UE_LOG(LogTemp, Error, TEXT("Not Possessing Tank"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Player Possesing %s"), *ControlledTank->GetName());
	}
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

