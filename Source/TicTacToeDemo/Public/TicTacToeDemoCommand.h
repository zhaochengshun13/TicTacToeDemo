// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TicTacToeDemoCommand.generated.h"

// This class does not need to be modified.
UCLASS(BlueprintType)
class UTicTacToeDemoCommand : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	virtual void DoCommand() const;

	UFUNCTION(BlueprintCallable)
	virtual void UndoCommand() const;
};

