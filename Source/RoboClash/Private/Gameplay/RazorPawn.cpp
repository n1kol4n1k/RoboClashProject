#include "Gameplay/RazorPawn.h"

float ARazorPawn::CalculateCurrentWeaponAngle(float DeltaTime)
{
	if (mWeaponState == RobotWeaponState::Inactive)
	{
		return 0.0f;
	}
	else //active
	{
		return mCurrentWeaponAngle = FMath::Wrap(mCurrentWeaponAngle - DeltaTime * mSawRotationSpeed, 0.f, 360.f);
	}
}


