// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/NavigationCharacter.h"

#include "World/Tiles/Tile.h"
#include "AI/AStarNavigation.h"


// Sets default values
ANavigationCharacter::ANavigationCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ANavigationCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANavigationCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANavigationCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ANavigationCharacter::SetStandingTile(ATile* Tile)
{
	if (!Tile->CanTakeCharacter())
		return;

	StandingTile = Tile;
	StandingTile->TakeCharacter(this);
	SetActorLocation(StandingTile->GetActorLocation() + FVector(0.0, 0.0, 100.0));
}

void ANavigationCharacter::SetMoveTarget(ATile* TargetTile)
{
	// Draw straight line to target
	const auto StartLocation = StandingTile->GetActorLocation() + FVector(0.0, 0.0, 110.0);
	const auto EndLocation = TargetTile->GetActorLocation() + FVector(0.0, 0.0, 110.0);
	DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Cyan, false, 10.0f, 0, 5.0f);

	// Get path with AStar
	MovementPath.Empty();
	MovementPath = UAStarNavigation::GetPath(StandingTile, TargetTile);

	// Draw path with lines
	auto LastTile = StandingTile;
	for (const auto Tile : MovementPath)
	{
		const auto Start = LastTile->GetActorLocation() + FVector(0.0, 0.0, 110.0);
		const auto End = Tile->GetActorLocation() + FVector(0.0, 0.0, 110.0);
		DrawDebugLine(GetWorld(), Start, End, FColor::Magenta, false, 10.0f, 0, 5.0f);

		LastTile = Tile;
	}
}
