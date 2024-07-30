// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/WheeledRobotPawn.h"
#include "ReaperPawn.generated.h"

/**
 * 
 */
UCLASS()
class ROBOCLASH_API AReaperPawn : public AWheeledRobotPawn
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
	float mHookSwingSpeed;

public:
	virtual float CalculateCurrentWeaponAngle(float DeltaTime) override;
};
