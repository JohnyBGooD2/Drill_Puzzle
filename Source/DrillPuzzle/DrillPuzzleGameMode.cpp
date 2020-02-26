// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "DrillPuzzleGameMode.h"
#include "DrillPuzzleHUD.h"
#include "DrillPuzzleCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "BuildCube.h"


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

	/*	spawnLocation += FVector(FMath::RandRange(-100.0f, 100.0f),
		FMath::RandRange(-100.0f, 100.0f), FMath::RandRange(-100.0f, 100.0f));

		spawnLocation = (spawnLocation - playerLocation).GetSafeNormal() * spawnDistance;*/

		//FVector SpawnLocation = FVector(FMath::RandRange(-800.0f, 800.0f), FMath::RandRange(-800.0f, 800.0f), 40.0f);


		World->SpawnActor<ABuildCube>(BuildCubeBlueprint, spawnLocation, FRotator::ZeroRotator);
		BuildCubesCount++;
		//GEngine->AddOnScreenDebugMessage(-1, 5.35f, FColor::Cyan.WithAlpha(255),
		//FString::Printf(TEXT("%d"), BuildCubesCount)); // %f - float %d - int

		// x - depth, y - width, z - height


		/*

		if (SpawnCounter.yCount < 100)
		{
			if (SpawnCounter.xCount < 100) //&& SpawnCounter.yCount < 1000) //&& SpawnCounter.zCount < 1000)
			{
				for (int x = 0; x < 10; x++)
				{
					World->SpawnActor<ABuildCube>(BuildCubeBlueprint, SpawnLocation, FRotator::ZeroRotator);
					SpawnCounter.xCount += 1;
					SpawnLocation.X += 10.0f;
				}
			}
			else
			{
				SpawnCounter.yCount += 1;
				SpawnCounter.xCount = 0;

				SpawnLocation.Y += 10.0f;
				SpawnLocation.X = 0.0f;
			}
			GEngine->AddOnScreenDebugMessage(-1, 5.35f, FColor::Cyan.WithAlpha(255),
			FString::Printf(TEXT("%d"), SpawnCounter.yCount)); // %f - float %d - int
		}

		*/
	}

}

void ADrillPuzzleGameMode::OnRestartAndReload()
{
	
	RestartLevelHandler.Broadcast();  // parameters in Broadcast() brackets
	BuildCubesCount = 0;
}


