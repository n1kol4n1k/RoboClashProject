#include "Gameplay/RobotController.h"
#include "RobotClashUtils.h"
#include "Gameplay/RoboClashGameInstance.h"
#include "Gameplay/BattleGameMode.h"
#include "Gameplay/BattleRobotState.h"
#include "UI/BattleOverlay.h"
#include "GameFramework/GameStateBase.h"
#include "UI/LeaderboardEntry.h"
#include "Kismet/GameplayStatics.h"

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

	ABattleRobotState* RobotState = GetPlayerState<ABattleRobotState>();
	RobotState->SetName(initData.ChosenRobotName);
	OnRep_PlayerState();
}

void ARobotController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalController())
	{
		HudInstance = CreateWidget<UBattleOverlay>(this, HudWidget);
		if (HudInstance)
		{
			HudInstance->AddToViewport();
			RefreshScoreboard();
		}
	}
}

void ARobotController::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	ARobotController* LocalController = Cast<ARobotController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	LocalController->RefreshScoreboard();
}

void ARobotController::RefreshScoreboard()
{
	if (IsLocalController() && IsValid(HudInstance))
	{
		ABattleRobotState* RobotState = GetPlayerState<ABattleRobotState>();
		AGameStateBase* GameStateBase = GetWorld()->GetGameState();
		for (int32 i = 1; i <= GameStateBase->PlayerArray.Num(); i++)
		{
			ABattleRobotState* CurrentPlayerState = Cast<ABattleRobotState>(GameStateBase->PlayerArray[i - 1]);
			ULeaderboardEntry* entry = HudInstance->GetEntry(i);

			entry->AddName(CurrentPlayerState->GetRobotName());
			entry->AddScore(CurrentPlayerState->GetRobotScore());
			if (CurrentPlayerState == RobotState)
			{
				entry->Highlight();
			}

			entry->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		}
	}
}
