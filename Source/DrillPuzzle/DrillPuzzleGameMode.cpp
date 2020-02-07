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
	if (World)
	{
		/*FVector SpawnLocation = FVector(FMath::RandRange(-800.0f, 800.0f), FMath::RandRange(-800.0f, 800.0f), 40.0f);
		World->SpawnActor<ABuildCube>(BuildCubeBlueprint, SpawnLocation, FRotator::ZeroRotator);*/

		float SpawnHeight = 0.0f;

		

		// x - depth, y - width, z - height

		if (SpawnCounter.zCount < 100)

		{

			if (SpawnCounter.xCount < 100) //&& SpawnCounter.yCount < 1000) //&& SpawnCounter.zCount < 1000)
			{
				for (int x = 0; x < 10; x++)
				{
					/*for (int y = 0; y < 1000; y++)
					{
						World->SpawnActor<ABuildCube>(BuildCubeBlueprint, SpawnLocation, FRotator::ZeroRotator);
						SpawnLocation.Y += 1.0f;
						SpawnCounter.yCount += 1;
					}*/
					//SpawnLocation.Y = 0.0f;
					//SpawnLocation.X += 1.0f;

					//SpawnCounter.xCount += 1;

					World->SpawnActor<ABuildCube>(BuildCubeBlueprint, SpawnLocation, FRotator::ZeroRotator);
					//SpawnLocation.X += 1.0f;
					SpawnCounter.xCount += 1;
					SpawnLocation.X += 10.0f;
				}

				//SpawnLocation.Y += 1.0f;
				//SpawnLocation.X = 0.0f;



				//SpawnCounter.xCount = 0

			}
			else
			{
				SpawnCounter.zCount += 1;
				SpawnCounter.xCount = 0;


				SpawnLocation.Z += 10.0f;
				SpawnLocation.X = 0.0f;
			}

			GEngine->AddOnScreenDebugMessage(-1, 5.35f, FColor::Cyan.WithAlpha(255),
			FString::Printf(TEXT("%d"), SpawnCounter.yCount)); // %f - float %d - int

		}

	}



	//SpawnCounter.xCount += 1;

	//int32 check = 1;

	

	//GEngine->AddOnScreenDebugMessage(-1, 5.35f, FColor::Cyan.WithAlpha(255),
	//FString::Printf(TEXT("%f"), (float)(SpawnCounter.xCount))); // %f - float %d - int
}


