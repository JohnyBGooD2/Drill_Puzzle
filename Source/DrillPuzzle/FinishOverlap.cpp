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

void AFinishOverlap::OnOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

	GetWorld()->GetTimerManager().SetTimer(delayToFinishHandle, this, &AFinishOverlap::OnDelayFinish, 5.0f, false, -1.0f); 

	//GetWorld()->GetTimerManager().ClearTimer(NameOfHandle);

	//GetWorld()->GetTimerManager().IsTimerActive(NameOfHandle);

}

void AFinishOverlap::OnDelayFinish()
{

	//GEngine->AddOnScreenDebugMessage(-1, 5.35f, FColor::Cyan.WithAlpha(255),
	//FString::Printf(TEXT("Hi"))); // %f - float %d - int

	ADrillPuzzleGameMode* CurrentGameMode = Cast<ADrillPuzzleGameMode>(GetWorld()->GetAuthGameMode());
	CurrentGameMode->OnRestartAndReload();
}

