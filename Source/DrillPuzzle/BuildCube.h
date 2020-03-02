// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DrillPuzzleGameMode.h"
#include "BuildCube.generated.h"


UCLASS()
class DRILLPUZZLE_API ABuildCube : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABuildCube();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool bAttract = false;
	bool bCharacterOverlapped = false;

	// Actor Components
	UPROPERTY(VisibleAnywhere)
	class UShapeComponent* OverlapBox;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* CubeMesh;

	UPROPERTY(VisibleAnywhere)
	ADrillPuzzleGameMode* CurrentGameMode;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void OnLevelRestartReload(); 


};
