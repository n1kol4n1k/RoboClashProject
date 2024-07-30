// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/TurtlePawn.h"

float ATurtlePawn::CalculateCurrentWeaponAngle(float DeltaTime)
{
	if (mWeaponState == RobotWeaponState::Inactive)
	{
		return 0.0f;
	}
	else //active
	{
		return mCurrentWeaponAngle = FMath::Wrap(mCurrentWeaponAngle - DeltaTime * mGrinderRotationSpeed, 0.f, 360.f);
	}
}
