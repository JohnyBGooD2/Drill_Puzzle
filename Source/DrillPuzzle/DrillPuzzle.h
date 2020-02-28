// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DrillPuzzle.generated.h"

USTRUCT()  //USTRUCT(BlueprintType)
struct FSpawnBuildCubesCounters
{
	GENERATED_USTRUCT_BODY() //GENERATED_BODY()

	UPROPERTY()
	int32 xCount = 0;

	UPROPERTY()
	int32 yCount = 0;

	UPROPERTY()
	int32 zCount = 0;

};

UENUM(BlueprintType)
enum class ETestEnum : uint8
{
	FirstEnumCheck			UMETA(DisplayName = "FirstEnumCheck_Display"),
	SecondEnumCheck			UMETA(DisplayName = "SecondEnumCheck_Display"),
	ThirdEnumCheck			UMETA(DisplayName = "ThirdEnumCheck_Display"),
	
};
