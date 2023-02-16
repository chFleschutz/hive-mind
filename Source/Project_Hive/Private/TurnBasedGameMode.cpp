// Fill out your copyright notice in the Description page of Project Settings.


#include "TurnBasedGameMode.h"


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
	ExecutionPhaseEvent.Broadcast();
}
