// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/BattleRobotState.h"
#include "Net/UnrealNetwork.h"

void ABattleRobotState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABattleRobotState, mName);
	DOREPLIFETIME(ABattleRobotState, mScore);
}
