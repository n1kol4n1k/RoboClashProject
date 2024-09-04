#include "Gameplay/RobotController.h"
#include "RobotClashUtils.h"
#include "Gameplay/RoboClashGameInstance.h"
#include "Gameplay/BattleGameMode.h"
#include "Gameplay/BattleRobotState.h"
#include "UI/BattleOverlay.h"
#include "GameFramework/GameStateBase.h"
#include "UI/LeaderboardEntry.h"


void ARobotController::RequestClientData_Implementation()
{
	if (!IsLocalController()) { return; }

	FInitRobotData initData;
	initData.ChosenRobotName = Cast<URoboClashGameInstance>(GetGameInstance())->ChosenRobotName;
	SendClientData(initData);

	ABattleRobotState* RobotState = GetPlayerState<ABattleRobotState>();
	if (RobotState)
	{
		RobotState->SetName(initData.ChosenRobotName);
	}
}

void ARobotController::SendClientData_Implementation(FInitRobotData initData)
{
	if (!HasAuthority()) { return; }

	ABattleGameMode* GameMode = Cast<ABattleGameMode>(GetWorld()->GetAuthGameMode());
	GameMode->SpawnRobotForPlayer(initData.ChosenRobotName, this);
	data = initData;
}

void ARobotController::BeginPlay()
{
	Super::BeginPlay();

	ABattleRobotState* RobotState = GetPlayerState<ABattleRobotState>();
	if (RobotState)
	{
		RobotState->SetName(data.ChosenRobotName);
	}

	if (IsLocalController())
	{
		HudInstance = CreateWidget<UBattleOverlay>(this, HudWidget);
		if (HudInstance)
		{
			HudInstance->AddToViewport();
		}

		AGameStateBase* GameStateBase = GetWorld()->GetGameState();
		for (int32 i = 1; i <= GameStateBase->PlayerArray.Num(); i++)
		{
			APlayerState* CurrentPlayerState = GameStateBase->PlayerArray[i - 1];
			ULeaderboardEntry* entry = HudInstance->GetEntry(i);

			entry->AddName(data.ChosenRobotName);
			entry->AddScore(CurrentPlayerState->GetScore());
			if (CurrentPlayerState == RobotState)
			{
				entry->Highlight();
			}

			entry->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		}
	}
}
