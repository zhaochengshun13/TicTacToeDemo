// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TicTacToeDemoSaveClass.h"
#include "Checkerboard.h"
#include "TicTacToeDemoGameMode.generated.h"

/** GameMode class to specify pawn and playercontroller */
UCLASS(minimalapi)
class ATicTacToeDemoGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ACheckerboard> CheckerboardClass;
	UPROPERTY(BlueprintReadWrite)
	ACheckerboard* Checkerboard;
	UPROPERTY(BlueprintReadWrite)
	UTicTacToeDemoSaveClass* TicTacToeDemoSave; 
	ATicTacToeDemoGameMode();

	UFUNCTION(BlueprintCallable)
	void EnterBattle();
};



