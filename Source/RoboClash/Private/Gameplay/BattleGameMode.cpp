#include "Gameplay/BattleGameMode.h"
#include "Gameplay/RobotController.h"
#include "Gameplay/BattleRobotState.h"

void ABattleGameMode::OnPostLogin(AController* NewPlayer)
{
	ARobotController* NewRobotController = Cast<ARobotController>(NewPlayer);
	if (IsValid(NewRobotController))
	{
		TSubclassOf<AWheeledRobotPawn> SpawnClass;
		ABattleRobotState* PlayerState = NewRobotController->GetPlayerState<ABattleRobotState>();
		
		if (!IsValid(PlayerState))
		{
			return;
		}
		
		const FName& RobotName = PlayerState->GetRobotName();

		if (RobotName == RazorTagName)
		{
			SpawnClass = RazorBP;
		}
		else if (RobotName == ReaperTagName)
		{
			SpawnClass = ReaperBP;
		}
		else if (RobotName == TurtleTagName)
		{
			SpawnClass = TurtleBP;
		}
		else
		{
			ensureAlwaysMsgf(false, TEXT("ERROR, unknown spawn class for player!"));
			return;
		}

		FActorSpawnParameters SpawnInfo;
		SpawnInfo.Instigator = GetInstigator();
		SpawnInfo.ObjectFlags |= RF_Transient;

		AActor* StartSpot = FindPlayerStart(NewPlayer);
		FRotator StartRotation(ForceInit);
		StartRotation.Yaw = StartSpot->GetActorRotation().Yaw;
		FVector StartLocation = StartSpot->GetActorLocation();

		FTransform SpawnTransform = FTransform(StartRotation, StartLocation);

		GetWorld()->SpawnActor<APawn>(SpawnClass, SpawnTransform, SpawnInfo);
	}
}
