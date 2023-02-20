// Fill out your copyright notice in the Description page of Project Settings.


#include "Checkerboard.h"

#include "MoveInChessCommand.h"
#include "Kismet/GameplayStatics.h"
#include "TicTacToeDemo/TicTacToeDemoGameMode.h"
#include "TicTacToeDemo/TicTacToeDemoBlock.h"

// Sets default values
ACheckerboard::ACheckerboard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
}

void ACheckerboard::BeginPlay()
{
	Super::BeginPlay();
	const int32 NumBlocks = Size * Size;
	for(int32 BlockIndex=0; BlockIndex<NumBlocks; BlockIndex++)
	{
		const float XOffset = (BlockIndex/Size) * CellSize; 
		const float YOffset = (BlockIndex%Size) * CellSize; 
			// Make position vector, offset from Grid location
		const FVector BlockLocation = FVector(XOffset, YOffset, 0.f) + GetActorLocation() - FVector(CellSize,CellSize,0);
			// Spawn a block
		ATicTacToeDemoBlock* NewBlock = GetWorld()->SpawnActor<ATicTacToeDemoBlock>(BlockLocation, FRotator(0,0,0));
		NewBlock->Pos=FVector2D(-1*(BlockIndex/Size-1),BlockIndex%Size-1);
		NewBlock->SetOwner(this);
	}
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Owner = this;
	MyAIController = GetWorld()->SpawnActor<ATicTacTeoAIController>(SpawnInfo);
}

void ACheckerboard::AIInput(EBoardSide Type, ATicTacToeDemoGameMode* TicTacToeDemo)
{
	if(Step%2 == ((TicTacToeDemo->TicTacToeDemoSave->PlayerFirst)?1:0))
	{
		MyAIController->Side=Type;
		MyAIController->BuildBoard();
		MyAIController->MinimaxSearch(CurDepth,TicTacToeDemo->TicTacToeDemoSave->AILevel);
		UMoveInChessCommand* Command = NewObject<UMoveInChessCommand>();
		TStrongObjectPtr<UTicTacToeDemoCommand> CommandPtr = TStrongObjectPtr<UTicTacToeDemoCommand>(Command);
		Command->Pos=MyAIController->GetBestPos()-FVector2D(1,1);
		Command->Checkerboard=this;
		Command->Type=Type;
		Command->DoCommand();
		EnqueueCommand(CommandPtr);
	}
}

void ACheckerboard::PutDownPieces(FVector2D Pos, EBoardSide Type)
{
	if(AActor** ChessPiece = PosToChessPiecesMap.Find(Pos))
	{
		(*ChessPiece)->Destroy();
	}
	AActor* Actor = nullptr;
	if(Type!=EBoardSide::None)
	{
		Actor = this->GetWorld()->SpawnActor<AActor>(Type==EBoardSide::SideA?SideAChessPieces:SideBChessPieces,GetPosFromBoardPos(Pos),FRotator::ZeroRotator);
		PosToChessPiecesMap.Add(Pos,Actor);
		CurDepth++;
		Step++;
		CurrentState.Add(Pos,Type);
	}
	else
	{
		CurrentState.Remove(Pos);
		CurDepth--;
		Step--;
	}
	if(Actor)
	{
		Actor->SetOwner(this);
	}

	CurSide=((CurSide==EBoardSide::SideA)?EBoardSide::SideB:EBoardSide::SideA);
	DynamicCurSideChangedMulticastDelegate.Broadcast(CurSide);
}

void ACheckerboard::MoveInChess(FVector2D Pos, EBoardSide Type)
{
	PutDownPieces(Pos, Type);

	if(JudgeVictory() != EBoardSide::None)
	{
		UE_LOG(LogTemp,Display,TEXT("End！！！"));
	}
	else if(ATicTacToeDemoGameMode* TicTacToeDemo = Cast<ATicTacToeDemoGameMode>(GetWorld()->GetAuthGameMode()))
	{
		if(TicTacToeDemo->TicTacToeDemoSave && TicTacToeDemo->TicTacToeDemoSave->EnableAI)
		{
			AIInput(CurSide, TicTacToeDemo);
		}
	}
}

FVector ACheckerboard::GetPosFromBoardPos(FVector2D Pos)
{
	return GetActorLocation() + FVector(Pos.X * -CellSize,Pos.Y*CellSize,0); 
}

EBoardSide ACheckerboard::JudgeVictory()
{
	for (auto Array : WinningSituation)
	{
		EBoardSide *Pos0 = CurrentState.Find(Array[0]);
		EBoardSide *Pos1 = CurrentState.Find(Array[1]);
		EBoardSide *Pos2 = CurrentState.Find(Array[2]);

		if(Pos0 && Pos1 && Pos2)
		{
			if((*Pos0) == EBoardSide::SideA
				&& (*Pos1) == EBoardSide::SideA
				&& (*Pos2) == EBoardSide::SideA)
			{
				return EBoardSide::SideA;
			}
			
			if((*Pos0) == EBoardSide::SideB
				&& (*Pos1) == EBoardSide::SideB
				&& (*Pos2) == EBoardSide::SideB)
			{
				return EBoardSide::SideB;
			}
		}
	}
	return EBoardSide::None;
}

void ACheckerboard::EnqueueCommand(TStrongObjectPtr<UTicTacToeDemoCommand>& Command)
{
	CommandQueue.Add(Command);
}

TStrongObjectPtr<UTicTacToeDemoCommand> ACheckerboard::DequeueCommand()
{
	if(CommandQueue.Num()>0)
		return CommandQueue.Pop();
	return nullptr;
}

void ACheckerboard::Undo()
{
	if(TStrongObjectPtr<UTicTacToeDemoCommand>  Command = DequeueCommand())
	{
		if(Command.IsValid())
		Command->UndoCommand();
	}
	if(TStrongObjectPtr<UTicTacToeDemoCommand>  Command2 = DequeueCommand())
	{
		if(Command2.IsValid())
			Command2->UndoCommand();
	}
}


