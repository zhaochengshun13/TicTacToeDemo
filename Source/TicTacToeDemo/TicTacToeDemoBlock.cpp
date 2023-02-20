// Copyright Epic Games, Inc. All Rights Reserved.

#include "TicTacToeDemoBlock.h"

#include "Checkerboard.h"
#include "MoveInChessCommand.h"
#include "TicTacToeDemoBlockGrid.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInstance.h"

ATicTacToeDemoBlock::ATicTacToeDemoBlock()
{
	// Structure to hold one-time initialization
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> PlaneMesh;
		ConstructorHelpers::FObjectFinderOptional<UMaterial> BaseMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> BlueMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> OrangeMaterial;
		FConstructorStatics()
			: PlaneMesh(TEXT("/Game/Puzzle/Meshes/PuzzleCube.PuzzleCube"))
			, BaseMaterial(TEXT("/Game/Puzzle/Meshes/BaseMaterial.BaseMaterial"))
			, BlueMaterial(TEXT("/Game/Puzzle/Meshes/BlueMaterial.BlueMaterial"))
			, OrangeMaterial(TEXT("/Game/Puzzle/Meshes/OrangeMaterial.OrangeMaterial"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	// Create dummy root scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	// Create static mesh component
	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh0"));
	BlockMesh->SetStaticMesh(ConstructorStatics.PlaneMesh.Get());
	BlockMesh->SetRelativeScale3D(FVector(1.f,1.f,0.05f));
	BlockMesh->SetRelativeLocation(FVector(0.f,0.f,5.f));
	BlockMesh->SetMaterial(0, ConstructorStatics.BlueMaterial.Get());
	BlockMesh->SetupAttachment(DummyRoot);
	BlockMesh->OnClicked.AddDynamic(this, &ATicTacToeDemoBlock::BlockClicked);
	BlockMesh->OnInputTouchBegin.AddDynamic(this, &ATicTacToeDemoBlock::OnFingerPressedBlock);

	// Save a pointer to the orange material
	BaseMaterial = ConstructorStatics.BaseMaterial.Get();
	BlueMaterial = ConstructorStatics.BlueMaterial.Get();
	OrangeMaterial = ConstructorStatics.OrangeMaterial.Get();
}

void ATicTacToeDemoBlock::BlockClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked)
{
	HandleClicked();
}


void ATicTacToeDemoBlock::OnFingerPressedBlock(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent)
{
	HandleClicked();
}

void ATicTacToeDemoBlock::HandleClicked()
{
	if(ACheckerboard* Checkerboard = Cast<ACheckerboard>(GetOwner()))
	{
		if(Checkerboard->JudgeVictory() == EBoardSide::SideA || Checkerboard->JudgeVictory() == EBoardSide::SideB)
		{
			return;
		}
		UMoveInChessCommand* Command = NewObject<UMoveInChessCommand>();
		Command->Pos=Pos;
		Command->Checkerboard=Checkerboard;
		//GetWorld()->GetGameState();
		Command->Type=Checkerboard->CurSide;
		Command->DoCommand();
		TStrongObjectPtr<UTicTacToeDemoCommand> CommandPtr = TStrongObjectPtr<UTicTacToeDemoCommand>(Command);
		Checkerboard->EnqueueCommand(CommandPtr);
		
	}
}