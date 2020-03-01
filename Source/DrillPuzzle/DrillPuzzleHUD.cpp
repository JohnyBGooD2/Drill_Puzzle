// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "DrillPuzzleHUD.h"
#include "Engine/Canvas.h"
#include "Engine/Texture2D.h"
#include "TextureResource.h"
#include "CanvasItem.h"
#include "UObject/ConstructorHelpers.h"

ADrillPuzzleHUD::ADrillPuzzleHUD()
{
	// Set the crosshair texture
	static ConstructorHelpers::FObjectFinder<UTexture2D> CrosshairTexObj(TEXT("/Game/FirstPerson/Textures/FirstPersonCrosshair"));
	CrosshairTex = CrosshairTexObj.Object;
}


void ADrillPuzzleHUD::DrawHUD()
{
	Super::DrawHUD();

	// Draw very simple crosshair

	// find center of the Canvas
	const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

	// offset by half the texture's dimensions so that the center of the texture aligns with the center of the Canvas
	//const FVector2D CrosshairDrawPosition((Center.X), (Center.Y));
	const FVector2D CrosshairDrawPosition(Canvas->SizeX/2, Canvas->SizeY/2);

	// draw the crosshair
	FCanvasTileItem TileItem( CrosshairDrawPosition, CrosshairTex->Resource, FLinearColor::White);
	TileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem( TileItem );

	// Draw Text
	FLinearColor TextColor = FColor::White;
	float ScreenX = 32.0f;
	float ScreenY = 32.0f;

	const FString LevelNumberInfo = TEXT("LMB - shoot and make platforms \nRMB - remove platforms\nGet to the finish!!!");

	if (LevelNumberInfo.IsEmpty() == false)
	{
		const float TextScale = 2.0f;
		const bool bDontScale = false;

		DrawText(LevelNumberInfo, TextColor, ScreenX, ScreenY, GEngine->GetMediumFont(), TextScale, bDontScale);
	}
}
