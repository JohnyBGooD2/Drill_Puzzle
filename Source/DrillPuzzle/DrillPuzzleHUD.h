// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DrillPuzzleHUD.generated.h"

UCLASS()
class ADrillPuzzleHUD : public AHUD
{
	GENERATED_BODY()

public:
	ADrillPuzzleHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

