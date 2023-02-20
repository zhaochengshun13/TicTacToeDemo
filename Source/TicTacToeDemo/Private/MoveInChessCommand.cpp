// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveInChessCommand.h"

void UMoveInChessCommand::DoCommand() const
{
	checkf(Checkerboard != nullptr, TEXT("UMoveInChessCommand::DoCommand() Checkerboard is nullptr"));
	Checkerboard->MoveInChess(Pos,Type);
}

void UMoveInChessCommand::UndoCommand() const
{
	checkf(Checkerboard != nullptr, TEXT("UMoveInChessCommand::UndoCommand() Checkerboard is nullptr"));
	Checkerboard->PutDownPieces(Pos,EBoardSide::None);
	Checkerboard->CurSide=((Type==EBoardSide::SideA)?EBoardSide::SideB:EBoardSide::SideA);
}
