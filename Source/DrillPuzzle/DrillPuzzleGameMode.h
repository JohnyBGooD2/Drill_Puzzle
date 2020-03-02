// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once
#define GETENUMSTRING(etype, evalue) ( (FindObject<UEnum>(ANY_PACKAGE, TEXT(etype), true) != nullptr) ? FindObject<UEnum>(ANY_PACKAGE, TEXT(etype), true)->GetEnumName((int32)evalue) : FString("Invalid - are you sure enum uses UENUM() macro?") )

#include "CoreMinimal.h"
#include "DrillPuzzle.h"
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
	FVector SpawnLocation;
	int32 BuildCubesCount;

};



