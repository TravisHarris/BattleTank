// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"


/**
 * 
 */
UCLASS()
class BATTETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
		virtual void BeginPlay() override;
		virtual void Tick(float DeltaTime) override;
		ATank* GetControlledTank() const;
		void AimAtCrosshair();
		bool GetCrosshairTarget(FVector& HitLocation);
		/* attempt at finding dynamic location of crosshair in viewport

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
		TSubclassOf<class UUserWidget> wTankUi;
		UUserWidget* Crosshair;
		*/
private:

	UPROPERTY(EditAnywhere)
	float CrosshairXLocation = 0.5f;

	UPROPERTY(EditAnywhere)
	float CrosshairYLocation = 0.33333f;

	UPROPERTY(EditAnywhere)
	float CrosshairLineTrace = 1000000.f;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& WorldDirection) const;
	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;

};
