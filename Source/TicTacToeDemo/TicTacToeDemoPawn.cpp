// Copyright Epic Games, Inc. All Rights Reserved.

#include "TicTacToeDemoPawn.h"
#include "TicTacToeDemoBlock.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

ATicTacToeDemoPawn::ATicTacToeDemoPawn(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer)
{
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

void ATicTacToeDemoPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ATicTacToeDemoPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("ResetVR", EInputEvent::IE_Pressed, this, &ATicTacToeDemoPawn::OnResetVR);
	PlayerInputComponent->BindAction("TriggerClick", EInputEvent::IE_Pressed, this, &ATicTacToeDemoPawn::TriggerClick);
}

void ATicTacToeDemoPawn::CalcCamera(float DeltaTime, struct FMinimalViewInfo& OutResult)
{
	Super::CalcCamera(DeltaTime, OutResult);

	OutResult.Rotation = FRotator(-90.0f, -90.0f, 0.0f);
}

void ATicTacToeDemoPawn::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ATicTacToeDemoPawn::TriggerClick()
{
	if (CurrentBlockFocus)
	{
		CurrentBlockFocus->HandleClicked();
	}
}
