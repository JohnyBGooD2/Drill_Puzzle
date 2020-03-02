// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelRange.h"
#include "Components/BoxComponent.h"
#include "DrillPuzzleCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "DrillPuzzleGameMode.h"

// Sets default values
ALevelRange::ALevelRange()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	OverlapBounds = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapBounds"));
	OverlapBounds->SetGenerateOverlapEvents(true);
	OverlapBounds->OnComponentEndOverlap.AddDynamic(this, &ALevelRange::OnEndOverlap);

}

// Called when the game starts or when spawned
void ALevelRange::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALevelRange::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// When Player out of level - restart
void ALevelRange::OnEndOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->IsA(ADrillPuzzleCharacter::StaticClass()))
	{
		ADrillPuzzleGameMode* CurrentGameMode = Cast<ADrillPuzzleGameMode>(GetWorld()->GetAuthGameMode());

		if (CurrentGameMode->IsValidLowLevel())
		{
			CurrentGameMode->OnRestartAndReload();
		}

	}
}

