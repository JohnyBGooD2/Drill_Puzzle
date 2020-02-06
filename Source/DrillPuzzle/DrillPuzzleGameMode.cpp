// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "DrillPuzzleGameMode.h"
#include "DrillPuzzleHUD.h"
#include "DrillPuzzleCharacter.h"
#include "BuildCube.h"
#include "UObject/ConstructorHelpers.h"


//USTRUCT()  //USTRUCT(BlueprintType)
//struct FSpawnBuildCubesCounters
//{
//	GENERATED_USTRUCT_BODY()
//
//	UPROPERTY()
//	int32 xCount = 0;
//
//	UPROPERTY()
//	int32 yCount = 0;
//
//	UPROPERTY()
//	int32 zCount = 0;
//
//};

//if (OtherActor->IsA(AEnemy::StaticClass()))

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
}

void ADrillPuzzleGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UWorld* World = GetWorld();
	if (World)
	{
		FVector SpawnLocation = FVector(FMath::RandRange(-800.0f, 800.0f), FMath::RandRange(-800.0f, 800.0f), 40.0f);
		World->SpawnActor<ABuildCube>(BuildCubeBlueprint, SpawnLocation, FRotator::ZeroRotator);

		//GEngine->AddOnScreenDebugMessage(-1, 5.35f, FColor::Cyan.WithAlpha(255),
  //      FString::Printf(TEXT("Spawned")));   // %s   GetCameraPanDirection().ToString()
	}

	SpawnCounter.xCount += 1;

	GEngine->AddOnScreenDebugMessage(-1, 5.35f, FColor::Cyan.WithAlpha(255), 
	FString::Printf(TEXT("%d"), SpawnCounter.xCount)); // %f - float %d - int
}


