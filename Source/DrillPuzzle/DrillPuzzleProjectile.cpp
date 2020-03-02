// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "DrillPuzzleProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "BuildCube.h"

ADrillPuzzleProjectile::ADrillPuzzleProjectile() 
{
	PrimaryActorTick.bCanEverTick = true;
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(37.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &ADrillPuzzleProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	ProjectileMovement->Velocity = FVector(0.0f, 0.0f, 0.0f);

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;

	// Create attract sphere
	AttractComp = CreateDefaultSubobject<USphereComponent>(TEXT("AttractComp"));
	AttractComp->InitSphereRadius(200.0f);
	AttractComp->SetupAttachment(CollisionComp);
	AttractComp->SetGenerateOverlapEvents(true);
	AttractComp->OnComponentBeginOverlap.AddDynamic(this, &ADrillPuzzleProjectile::OnAttractOverlap);
}

void ADrillPuzzleProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	float distToPlayer = GetDistanceTo(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (distToPlayer > 1000.0f)
	{
		Destroy();
	}
}

void ADrillPuzzleProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	this->Destroy();
}

// Attract cubes and convert them to platforms
void ADrillPuzzleProjectile::OnAttractOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor->IsA(ABuildCube::StaticClass()))
	{
		Cast<ABuildCube>(OtherActor)->bAttract = true;
	}
}