#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "WheeledRobotPawn.h"
#include "BattleGameMode.generated.h"

UCLASS()
class ROBOCLASH_API ABattleGameMode : public AGameModeBase
{
	GENERATED_BODY()
private:
	UPROPERTY(EditDefaultsOnly)
	FName RazorTagName;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AWheeledRobotPawn> RazorBP;
	
	UPROPERTY(EditDefaultsOnly)
	FName ReaperTagName;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AWheeledRobotPawn> ReaperBP;

	UPROPERTY(EditDefaultsOnly)
	FName TurtleTagName;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AWheeledRobotPawn> TurtleBP;



protected:
	virtual void OnPostLogin(AController* NewPlayer) override;
};
