#include "Gameplay/RobotController.h"
#include "RobotClashUtils.h"
#include "Gameplay/RoboClashGameInstance.h"
#include "Gameplay/BattleGameMode.h"

void ARobotController::RequestClientData_Implementation()
{
	if (!IsLocalController()) { return; }

	FInitRobotData initData;
	initData.ChosenRobotName = Cast<URoboClashGameInstance>(GetGameInstance())->ChosenRobotName;
	SendClientData(initData);
}

void ARobotController::SendClientData_Implementation(FInitRobotData initData)
{
	if (!HasAuthority()) { return; }

	ABattleGameMode* GameMode = Cast<ABattleGameMode>(GetWorld()->GetAuthGameMode());
	GameMode->SpawnRobotForPlayer(initData.ChosenRobotName, this);
}
