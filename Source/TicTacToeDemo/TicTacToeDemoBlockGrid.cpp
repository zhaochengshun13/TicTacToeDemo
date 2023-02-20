// Copyright Epic Games, Inc. All Rights Reserved.

#include "TicTacToeDemoBlockGrid.h"
#include "Components/TextRenderComponent.h"

#define LOCTEXT_NAMESPACE "PuzzleBlockGrid"

ATicTacToeDemoBlockGrid::ATicTacToeDemoBlockGrid()
{
	// Create dummy root scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	// Create static mesh component
	ScoreText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("ScoreText0"));
	ScoreText->SetRelativeLocation(FVector(200.f,0.f,0.f));
	ScoreText->SetRelativeRotation(FRotator(90.f,0.f,0.f));
	ScoreText->SetText(FText::Format(LOCTEXT("ScoreFmt", "Score: {0}"), FText::AsNumber(0)));
	ScoreText->SetupAttachment(DummyRoot);

	// Set defaults
	Size = 3;
	BlockSpacing = 300.f;
}


void ATicTacToeDemoBlockGrid::BeginPlay()
{
	Super::BeginPlay();
}


#undef LOCTEXT_NAMESPACE
