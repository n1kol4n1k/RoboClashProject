// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/WheeledRobotPawn.h"
#include "RazorPawn.generated.h"

/**
 * 
 */
UCLASS()
class ROBOCLASH_API ARazorPawn : public AWheeledRobotPawn
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
	float mSawRotationSpeed;

public:
	virtual float CalculateCurrentWeaponAngle(float DeltaTime) override;
};
