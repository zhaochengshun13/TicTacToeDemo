// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "TicTacToeDemoSaveClass.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class TICTACTOEDEMO_API UTicTacToeDemoSaveClass : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,  Category = Basic)
	FName SlotName = TEXT("TicTacToeDemoSave");
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = Basic)
	int AILevel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Basic)
	bool PlayerFirst;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Basic)
	bool EnableAI = true;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,  Category = Basic)
	UClass* SideAChessPiece;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,  Category = Basic)
	UClass* SideBChessPiece;
};
