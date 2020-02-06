// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DrillPuzzle.generated.h"

USTRUCT()  //USTRUCT(BlueprintType)
struct FSpawnBuildCubesCounters
{
	GENERATED_USTRUCT_BODY() //GENERATED_BODY()

	UPROPERTY()
	int32 xCount;

	UPROPERTY()
	int32 yCount;

	UPROPERTY()
	int32 zCount;

};