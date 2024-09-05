#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "BattleRobotState.generated.h"

UCLASS()
class ROBOCLASH_API ABattleRobotState : public APlayerState
{
	GENERATED_BODY()

protected:
	UPROPERTY(Transient, BlueprintReadWrite, Replicated)
	FName mName;

	UPROPERTY(Transient, BlueprintReadWrite, ReplicatedUsing=OnRep_ScoreChanged)
	int32 mScore = 0;

public:
	void SetName(const FName& name) { mName = name; }
	void AddScore(uint32 scoreToAdd) { mScore += scoreToAdd; OnRep_ScoreChanged(); }

	FName GetRobotName() const { return mName; }
	int32 GetRobotScore() const { return mScore; }

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	UFUNCTION()
	void OnRep_ScoreChanged();
};
