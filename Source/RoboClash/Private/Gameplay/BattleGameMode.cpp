#include "Gameplay/BattleGameMode.h"
#include "Gameplay/RobotController.h"
#include "Gameplay/BattleRobotState.h"
#include "EngineUtils.h"
#include "GameFramework/PlayerStart.h"
#include "Algo/MaxElement.h"

void ABattleGameMode::StartPlay()
{
	Super::StartPlay();
}

void ABattleGameMode::OnPostLogin(AController* NewPlayer)
{
	if (AvailableSpawnPoints.IsEmpty())
	{
		UWorld* World = GetWorld();
		for (TActorIterator<APlayerStart> It(World); It; ++It)
		{
			APlayerStart* PlayerStart = *It;
			AvailableSpawnPoints.Add(PlayerStart);
		}
	}

	ARobotController* NewRobotController = Cast<ARobotController>(NewPlayer);
	NewRobotController->RequestClientData();
}

void ABattleGameMode::SpawnRobotForPlayer(FName& robotName, ARobotController* player)
{
	if (IsValid(player))
	{
		TSubclassOf<AWheeledRobotPawn> SpawnClass;

		if (robotName == RazorTagName)
		{
			SpawnClass = RazorBP;
		}
		else if (robotName == ReaperTagName)
		{
			SpawnClass = ReaperBP;
		}
		else if (robotName == TurtleTagName)
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

		AActor* StartSpot = FindOptimalSpawnPoint(player);
		FRotator StartRotation(ForceInit);
		StartRotation.Yaw = StartSpot->GetActorRotation().Yaw;
		FVector StartLocation = StartSpot->GetActorLocation();

		FTransform SpawnTransform = FTransform(StartRotation, StartLocation);

		APawn* NewPawn = GetWorld()->SpawnActor<APawn>(SpawnClass, SpawnTransform, SpawnInfo);
		if (IsValid(NewPawn))
		{
			player->Possess(NewPawn);
		}
	}
}

AActor* ABattleGameMode::FindOptimalSpawnPoint(APlayerController* forPlayer) const
{
	TArray<TPair<APlayerStart*, int32>> AvailableSpawnPointsWithWeights;

	UWorld* World = GetWorld();

	for (APlayerStart* PlayerStart : AvailableSpawnPoints)
	{
		TPair<APlayerStart*, int32>& CurrSpawnWithWeight =
			AvailableSpawnPointsWithWeights[AvailableSpawnPointsWithWeights.Add(TPair<APlayerStart*, int32>(PlayerStart, 0))];
		
		for (TActorIterator<APlayerController> It(World); It; ++It)
		{
			APlayerController* PlayerController = *It;
			if (forPlayer == PlayerController)
			{
				continue;
			}

			AActor* PlayerActor = PlayerController->GetPawn();
			if (PlayerController && PlayerActor)
			{
				FVector LocationSpawnPoint = PlayerStart->GetActorLocation();
				FVector LocationPlayer = PlayerActor->GetActorLocation();

				// Calculate distance between the two locations
				float Distance = FVector::Dist(LocationSpawnPoint, LocationPlayer);
				CurrSpawnWithWeight.Value += Distance;
			}
		}
	}

	TPair<APlayerStart*, int32>* BestSpawnPoint = Algo::MaxElement(
		AvailableSpawnPointsWithWeights, [](const TPair<APlayerStart*, int32>& A, const TPair<APlayerStart*, int32>& B)
		{
			return A.Value < B.Value;
		});

	return BestSpawnPoint->Key;
}

