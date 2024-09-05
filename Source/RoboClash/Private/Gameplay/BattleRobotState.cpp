#include "Gameplay/BattleRobotState.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"
#include "Gameplay/RobotController.h"

void ABattleRobotState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABattleRobotState, mName);
	DOREPLIFETIME(ABattleRobotState, mScore);
}

void ABattleRobotState::OnRep_ScoreChanged()
{
	ARobotController* LocalController = Cast<ARobotController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	LocalController->RefreshScoreboard();
}
