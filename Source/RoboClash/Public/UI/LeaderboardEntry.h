#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LeaderboardEntry.generated.h"


UCLASS()
class ROBOCLASH_API ULeaderboardEntry : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void AddScore(int32 RobotScore);

	UFUNCTION(BlueprintImplementableEvent)
	void AddName(FName RobotName);

	UFUNCTION(BlueprintImplementableEvent)
	void Highlight();
};
