// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Checkerboard.h"
#include "TicTacToeDemoCommand.h"
#include "MoveInChessCommand.generated.h"

UCLASS(BlueprintType)
class TICTACTOEDEMO_API UMoveInChessCommand : public UTicTacToeDemoCommand
{
	GENERATED_BODY()
public:

	UPROPERTY()
	ACheckerboard* Checkerboard;
	UPROPERTY(VisibleAnywhere)
	FVector2D Pos;
	UPROPERTY(VisibleAnywhere)
	EBoardSide Type;

	virtual void DoCommand() const override;

	virtual void UndoCommand() const override;
};
