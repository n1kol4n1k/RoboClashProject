#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BattleOverlay.generated.h"

UCLASS()
class ROBOCLASH_API UBattleOverlay : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta=(BindWidget))
	class ULeaderboardEntry* Entry1;

	UPROPERTY(meta = (BindWidget))
	class ULeaderboardEntry* Entry2;

	UPROPERTY(meta = (BindWidget))
	class ULeaderboardEntry* Entry3;

	UPROPERTY(meta = (BindWidget))
	class ULeaderboardEntry* Entry4;

public:
	ULeaderboardEntry* GetEntry(int32 num) const;
};
