// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TicTacTeoAIController.h"
#include "TicTacToeDemoCommand.h"
#include "UObject/StrongObjectPtr.h"
#include "Checkerboard.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDynamicCurSideChangedMulticastDelegate, EBoardSide, Sde);


UCLASS(BlueprintType)

class TICTACTOEDEMO_API ACheckerboard : public AActor
{
	GENERATED_BODY()
protected:
	// Begin AActor interface
	virtual void BeginPlay() override;

public:

	// Sets default values for this actor's properties
	ACheckerboard();

	UPROPERTY(BlueprintReadWrite)
	EBoardSide CurSide = EBoardSide::SideA;

	UPROPERTY(EditDefaultsOnly)
	ATicTacTeoAIController* MyAIController;
	
	UPROPERTY(Category=Grid, EditAnywhere, BlueprintReadOnly)
	int32 Size = 3;

	UPROPERTY(BlueprintAssignable)
	FDynamicCurSideChangedMulticastDelegate DynamicCurSideChangedMulticastDelegate;
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMeshComponent;
	
	UPROPERTY(EditAnywhere)
	float CellSize;
	UPROPERTY(VisibleAnywhere,meta = (DisplayName = "棋盘当前状态",ToolTip = "X正方向从左到右，Y正方向从上到下，中心点为0,0 记录棋盘信息"))
	TMap<FVector2D,EBoardSide> CurrentState;
	
	TMap<FVector2D,AActor*> PosToChessPiecesMap;
	

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UClass* SideAChessPieces;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UClass* SideBChessPieces;

	UPROPERTY(VisibleAnywhere)
	int CurDepth = 0;
	UPROPERTY(VisibleAnywhere)
	int SearchDepth = 8;

	UFUNCTION(BlueprintCallable)
	void MoveInChess(FVector2D Pos,EBoardSide Type);
	UFUNCTION(BlueprintCallable)
	FVector GetPosFromBoardPos(FVector2D Pos);
	
	UFUNCTION(BlueprintCallable)
		EBoardSide JudgeVictory();

public:	
	void EnqueueCommand(TStrongObjectPtr<UTicTacToeDemoCommand>& Command);
	TStrongObjectPtr<UTicTacToeDemoCommand> DequeueCommand();
	UFUNCTION(BlueprintCallable)
	void Undo();
	void PutDownPieces(FVector2D Pos, EBoardSide Type);
private:
	//穷举胜利条件
	TArray<TArray<FVector2D>> WinningSituation={
		TArray<FVector2D>{FVector2D(-1,-1),FVector2D(-1,0),FVector2D(-1,1)},
		TArray<FVector2D>{FVector2D(0,-1),FVector2D(0,0),FVector2D(0,1)},
		TArray<FVector2D>{FVector2D(1,-1),FVector2D(1,0),FVector2D(1,1)},
		
		TArray<FVector2D>{FVector2D(-1,-1),FVector2D(0,0),FVector2D(1,1)},
		TArray<FVector2D>{FVector2D(-1,1),FVector2D(0,0),FVector2D(1,-1)},
		
		TArray<FVector2D>{FVector2D(-1,-1),FVector2D(0,-1),FVector2D(1,-1)},
		TArray<FVector2D>{FVector2D(-1,0),FVector2D(0,0),FVector2D(1,0)},
		TArray<FVector2D>{FVector2D(-1,1),FVector2D(0,1),FVector2D(1,1)},
	};
	void AIInput(EBoardSide Type,class ATicTacToeDemoGameMode* TicTacToeDemo);

	
protected:
	TArray<TStrongObjectPtr<UTicTacToeDemoCommand>> CommandQueue;
	int Step=0;
};