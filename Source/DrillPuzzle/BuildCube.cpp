// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildCube.h"
#include "Components/BoxComponent.h"
#include "DrillPuzzleProjectile.h"
#include "DrillPuzzleCharacter.h"



//IsValidLowLevel()

// Sets default values
ABuildCube::ABuildCube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	OverlapBox = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapBox"));
	OverlapBox->SetGenerateOverlapEvents(true);
	OverlapBox->OnComponentBeginOverlap.AddDynamic(this, &ABuildCube::OnOverlap);
	OverlapBox->OnComponentEndOverlap.AddDynamic(this, &ABuildCube::OnEndOverlap);

	RootComponent = OverlapBox;

	CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeMesh"));  
	CubeMesh->SetupAttachment(OverlapBox); 

	//CurrentGameMode = Cast<ADrillPuzzleGameMode>(GetWorld()->GetAuthGameMode());

	//if (CurrentGameMode->IsValidLowLevel())
	//{
	//CurrentGameMode->RestartLevelHandler.AddDynamic(this, &ABuildCube::OnLevelRestartReload);
	//}
}

// Called when the game starts or when spawned  
void ABuildCube::BeginPlay()
{
	Super::BeginPlay();
	CurrentGameMode = Cast<ADrillPuzzleGameMode>(GetWorld()->GetAuthGameMode());
	if (CurrentGameMode->IsValidLowLevel())
	{
	    CurrentGameMode->RestartLevelHandler.AddDynamic(this, &ABuildCube::OnLevelRestartReload);
	}
	
	
}

// Called every frame
void ABuildCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bAttract == true)
	{

		//GEngine->AddOnScreenDebugMessage(-1, 5.35f, FColor::Cyan.WithAlpha(255),
		//FString::Printf(TEXT("AttractTrue")));//, SpawnCounter.yCount)); // %f - float %d - int

		TArray<AActor*> ProjectilesOverlapped;
		//OverlapBox->GetOverlappingActors(ProjectilesOverlapped, TSubclassOf<ADrillPuzzleProjectile>());
		OverlapBox->GetOverlappingActors(ProjectilesOverlapped, ADrillPuzzleProjectile::StaticClass());

		TArray<AActor*> CharacterOverlapped;
		OverlapBox->GetOverlappingActors(CharacterOverlapped, ADrillPuzzleCharacter::StaticClass());

		//GEngine->AddOnScreenDebugMessage(-1, 5.35f, FColor::Cyan.WithAlpha(255),
		//FString::Printf(TEXT("%d"), ProjectilesOverlapped.Num()));//, SpawnCounter.yCount)); // %f - float %d - int

		/*GEngine->AddOnScreenDebugMessage(-1, 5.35f, FColor::Cyan.WithAlpha(255),
		FString::Printf(TEXT("%s"), this->bCharacterOverlapped ? TEXT("True") : TEXT("False")));*/

		if (ProjectilesOverlapped.Num() > 0) //&& CharacterOverlapped.Num() == 0)
		{
				FVector NewLocation = GetActorLocation() + (ProjectilesOverlapped[0]->GetActorLocation() - GetActorLocation()) * DeltaTime * 2.5f;//.GetSafeNormal()
				SetActorLocation(NewLocation);
				if (GetActorScale3D().X < 2.0f)
				{
					FVector NewScale = FVector(GetActorScale3D().X * (1.0f + DeltaTime * 2.0f), GetActorScale3D().Y * (1.0f + DeltaTime * 2.0f), GetActorScale3D().Z);
					SetActorScale3D(NewScale);
				}
		}
		else
		{
			bAttract = false;
		}
	}

}

void ABuildCube::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (OtherActor->IsA(ADrillPuzzleCharacter::StaticClass()))
	{
		bCharacterOverlapped = true;
	}
}

void ABuildCube::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->IsA(ADrillPuzzleCharacter::StaticClass()))
	{
		bCharacterOverlapped = false;
	}
}

void ABuildCube::OnLevelRestartReload()
{
	/*GEngine->AddOnScreenDebugMessage(-1, 5.35f, FColor::Cyan.WithAlpha(255),
	FString::Printf(TEXT("I hear level restart")));*/

	Destroy();
}
