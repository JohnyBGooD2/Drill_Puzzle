// Fill out your copyright notice in the Description page of Project Settings.


#include "FinishOverlap.h"
#include "Components/BoxComponent.h"
#include "DrillPuzzleGameMode.h"



// Sets default values
AFinishOverlap::AFinishOverlap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OverlapBox = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapBox"));
	OverlapBox->SetGenerateOverlapEvents(true);
	OverlapBox->OnComponentBeginOverlap.AddDynamic(this, &AFinishOverlap::OnOverlap);

}

// Called when the game starts or when spawned
void AFinishOverlap::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFinishOverlap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Level Completed on Overlap
void AFinishOverlap::OnOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	GetWorld()->GetTimerManager().SetTimer(delayToFinishHandle, this, &AFinishOverlap::OnDelayFinish, 5.0f, false, -1.0f); 
}

// Delay before restart level
void AFinishOverlap::OnDelayFinish()
{
	ADrillPuzzleGameMode* CurrentGameMode = Cast<ADrillPuzzleGameMode>(GetWorld()->GetAuthGameMode());
	CurrentGameMode->OnRestartAndReload();
}

