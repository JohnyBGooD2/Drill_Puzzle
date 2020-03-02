// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "DrillPuzzleGameMode.h"
#include "DrillPuzzleHUD.h"
#include "DrillPuzzleCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "BuildCube.h"


ADrillPuzzleGameMode::ADrillPuzzleGameMode(): Super()
{
	PrimaryActorTick.bCanEverTick = true;

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ADrillPuzzleHUD::StaticClass();

	static ConstructorHelpers::FClassFinder<ABuildCube> BuildCubeClassFinder(TEXT("/Game/Build/BP_BuildCube"));
	BuildCubeBlueprint = BuildCubeClassFinder.Class;
}

void ADrillPuzzleGameMode::BeginPlay()
{
	Super::BeginPlay();
	SpawnLocation = FVector(0.0f, 0.0f, 140.0f);
}

void ADrillPuzzleGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UWorld* World = GetWorld();
	if (World && BuildCubesCount < 3500)
	{
		FVector playerLocation = World->GetFirstPlayerController()->GetPawn()->GetActorLocation();
		float spawnDistance = FMath::RandRange(500.0f, 1500.0f);
		FVector spawnLocation = playerLocation;
		float randomAngle = FMath::RandRange(0.0f, 360.0f);

		spawnLocation.X += FMath::Cos(randomAngle * 3.14f / 180.0f) * spawnDistance;
		spawnLocation.Y += FMath::Sin(randomAngle * 3.14f / 180.0f) * spawnDistance;
		spawnLocation.Z += FMath::RandRange(-1000.0f, 1000.0f);

		World->SpawnActor<ABuildCube>(BuildCubeBlueprint, spawnLocation, FRotator::ZeroRotator);
		BuildCubesCount++;
	}

}

// Restart not reopening level
void ADrillPuzzleGameMode::OnRestartAndReload()
{
	
	ADrillPuzzleCharacter* playerCharacter = Cast<ADrillPuzzleCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	playerCharacter->SetActorLocation(FVector(-351.0f, -29.0f, 265.0f));
	GetWorld()->GetFirstPlayerController()->SetControlRotation(FRotator(0.0f, 0.0f, 0.0f));

	RestartLevelHandler.Broadcast(); 
	BuildCubesCount = 0;
}


