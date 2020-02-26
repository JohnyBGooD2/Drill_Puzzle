// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DrillPuzzle.h"
//#include "BuildCube.h"
#include "GameFramework/GameModeBase.h"
#include "DrillPuzzleGameMode.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLevelRestartAndReload);

UCLASS(minimalapi)
class ADrillPuzzleGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ADrillPuzzleGameMode();
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "My_Spawning")
	TSubclassOf<class ABuildCube> BuildCubeBlueprint;

	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
	FOnLevelRestartAndReload RestartLevelHandler;

	void OnRestartAndReload();

private:
	FSpawnBuildCubesCounters SpawnCounter;
	FVector SpawnLocation;
	int32 BuildCubesCount;

};



