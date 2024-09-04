#include "UI/BattleOverlay.h"

ULeaderboardEntry* UBattleOverlay::GetEntry(int32 num) const
{
	switch (num)
	{
	case 1:
		return Entry1;
	case 2:
		return Entry2;
	case 3:
		return Entry3;
	case 4:
		return Entry4;
	default:
		return Entry1;
	}
}