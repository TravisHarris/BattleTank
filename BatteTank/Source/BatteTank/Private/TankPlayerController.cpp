// Fill out your copyright notice in the Description page of Project Settings.


#include "BatteTank.h"
#include "TankPlayerController.h"
//#include "Blueprint/UserWidget.h"



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
	/*
	if (wTankUi) {
		Crosshair = CreateWidget<UUserWidget>(this, wTankUi);
	}
	*/
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimAtCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimAtCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation; // OUT Parameter
	if (GetCrosshairTarget(HitLocation)) {
		GetControlledTank()->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetCrosshairTarget(FVector& HitLocation)
{
	/// get crosshair's location on screen in pixels
	int32 ViewportSizeX, ViewportSizeY; // OUT params
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
	//UE_LOG(LogTemp, Warning, TEXT("Crosshair Location: %s"), *ScreenLocation.ToString());

	/* attempt at finding dynamic location of crosshair in viewport

	Crosshair = this->Crosshair->GetSlateWidgetFromName("Crosshair")->GetRenderTransform()->GetTranslation();
	*/

	// de-project the screen psition of the crosshair to a orld direction

	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection)) {
		// line trace along that direction
		FHitResult HitResult; // OUT param
		if (GetLookVectorHitLocation(LookDirection, HitLocation)) {
			//UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *HitLocation.ToString());
		}
	}

	
	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& WorldDirection) const
{
	FVector CameraWorldLocation; //placeholder
	return DeprojectScreenPositionToWorld
			(ScreenLocation.X, 
			ScreenLocation.Y, 
			CameraWorldLocation, 
			WorldDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	FVector StartLine = PlayerCameraManager->GetCameraLocation();
	FVector EndLine = StartLine + (LookDirection * CrosshairLineTrace);
	if (GetWorld()->LineTraceSingleByChannel
		(HitResult,
		StartLine,
		EndLine,
		ECollisionChannel::ECC_Visibility))
	{
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0);
	return false; // line trace did not succeed
}