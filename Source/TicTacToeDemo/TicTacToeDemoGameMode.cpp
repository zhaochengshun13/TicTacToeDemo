// Copyright Epic Games, Inc. All Rights Reserved.

#include "TicTacToeDemoGameMode.h"

#include "MoveInChessCommand.h"
#include "TicTacToeDemoPlayerController.h"
#include "TicTacToeDemoPawn.h"

ATicTacToeDemoGameMode::ATicTacToeDemoGameMode()
{
	// no pawn by default
	DefaultPawnClass = ATicTacToeDemoPawn::StaticClass();
	// use our own player controller class
	PlayerControllerClass = ATicTacToeDemoPlayerController::StaticClass();
	TicTacToeDemoSave = CreateDefaultSubobject<UTicTacToeDemoSaveClass>(TEXT("TicTacToeDemoSave"));
}

void ATicTacToeDemoGameMode::EnterBattle()
{
	Checkerboard = GetWorld()->SpawnActor<ACheckerboard>(CheckerboardClass,FVector::ZeroVector,FRotator::ZeroRotator);
	if(TicTacToeDemoSave && TicTacToeDemoSave->PlayerFirst==false)
	{
		Checkerboard->PutDownPieces(FVector2D(FMath::RandRange(-1, 1),FMath::RandRange(-1, 1)),EBoardSide::SideB);
		Checkerboard->CurSide=EBoardSide::SideA;
	}
}

