// Fill out your copyright notice in the Description page of Project Settings.


#include "TurnBasedGameMode.h"

#include "AI/NavigableUnit.h"

#include "Kismet/GameplayStatics.h"

ATurnBasedGameMode::ATurnBasedGameMode()
{
}

void ATurnBasedGameMode::PlayerFinishedTurn()
{
	NumPlayerReady++;
	if (NumPlayerReady < GetNumPlayers())
		return;

	ExecutePlayerTurns();
}

void ATurnBasedGameMode::ExecutePlayerTurns()
{
	NumPlayerReady = 0;

	TArray<AActor*> Units;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ANavigableUnit::StaticClass(), Units);

	for (const auto Actor : Units)
	{
		if (const auto Unit = Cast<ANavigableUnit>(Actor))
		{
			Unit->StartMoveToTarget();
		}
	}
}
