// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/ReaperPawn.h"

float AReaperPawn::CalculateCurrentWeaponAngle(float DeltaTime)
{
	static bool IsForward = true;
	if (mWeaponState == RobotWeaponState::Inactive)
	{
		return 0.0f;
	}
	else //active
	{
		IsForward = IsForward && mCurrentWeaponAngle > -180.f;
		if (IsForward)
		{
			mCurrentWeaponAngle = mCurrentWeaponAngle - DeltaTime * mHookSwingSpeed;
		}
		else
		{
			mCurrentWeaponAngle = mCurrentWeaponAngle + DeltaTime * mHookSwingSpeed;
			if (mCurrentWeaponAngle >= 0) //reset state after animation is complete
			{
				mWeaponState = RobotWeaponState::Inactive;
				IsForward = true;
			}
		}
		return mCurrentWeaponAngle;
	}
}

void AReaperPawn::HandleToggleWeaponInput()
{
	mWeaponState = RobotWeaponState::Active;
}

bool AReaperPawn::CheckHitAvailable()
{
	const float CurrentTime = GetWorld()->GetTimeSeconds();
	const bool rtn = CurrentTime - mLastHitTime > mHitCooldown;
	if (rtn)
	{
		mLastHitTime = CurrentTime;
	}
	return rtn;
}
