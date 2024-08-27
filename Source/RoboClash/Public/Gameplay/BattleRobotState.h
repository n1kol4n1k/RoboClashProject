#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "BattleRobotState.generated.h"

UCLASS()
class ROBOCLASH_API ABattleRobotState : public APlayerState
{
	GENERATED_BODY()

protected:
	UPROPERTY(Transient, BlueprintReadWrite)
	FName mRobotName;

public:
	const FName& GetRobotName() const { return mRobotName; }
};
