#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RobotController.generated.h"

USTRUCT()
struct FInitRobotData
{
	GENERATED_BODY()
public:
	UPROPERTY()
	FName ChosenRobotName;
};

UCLASS()
class ROBOCLASH_API ARobotController : public APlayerController
{
	GENERATED_BODY()

public:
	UFUNCTION(Client, Reliable)
	void RequestClientData();
	void RequestClientData_Implementation();

	UFUNCTION(Server, Reliable)
	void SendClientData(FInitRobotData initData);
	void SendClientData_Implementation(FInitRobotData initData);
};
