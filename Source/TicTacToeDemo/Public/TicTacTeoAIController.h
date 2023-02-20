// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TicTacTeoAIController.generated.h"

#define InitCheckerboard check(GetOwner()!=nullptr)\
	ACheckerboard* Checkerboard = Cast<ACheckerboard>(GetOwner());\
check(Checkerboard!=nullptr)

UENUM(BlueprintType)
enum class EBoardSide : uint8
{
	None UMETA(ToolTip="无"),
	SideA UMETA(ToolTip="势力A"),
	SideB UMETA(ToolTip="势力B")
};
//算法来源：https://www.freesion.com/article/68291482013/
UCLASS()
class TICTACTOEDEMO_API ATicTacTeoAIController : public AAIController
{
 	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	int MinimaxSearch(int Depth,int Searchdepth = 9);
	UFUNCTION(BlueprintCallable)
	int Evaluate();

	UFUNCTION(BlueprintCallable)
	inline FVector2D GetBestPos(){ return BestPos; }

	void BuildBoard();
	
    int IsEnd();

    EBoardSide Side = EBoardSide::SideA;
private:
	FVector2D BestPos;
	
	TArray<TArray<int>> Board;
};
