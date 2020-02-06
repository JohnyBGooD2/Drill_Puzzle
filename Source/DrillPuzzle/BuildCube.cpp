// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildCube.h"
#include "Components/BoxComponent.h"


// Sets default values
ABuildCube::ABuildCube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	OverlapBox = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapBox"));
	OverlapBox->SetGenerateOverlapEvents(true);

	RootComponent = OverlapBox;

	CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeMesh"));
	CubeMesh->SetupAttachment(OverlapBox);

}

// Called when the game starts or when spawned
void ABuildCube::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABuildCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

