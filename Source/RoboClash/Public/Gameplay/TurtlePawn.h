// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/WheeledRobotPawn.h"
#include "TurtlePawn.generated.h"

/**
 * 
 */
UCLASS()
class ROBOCLASH_API ATurtlePawn : public AWheeledRobotPawn
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly)
	float mGrinderRotationSpeed;

public:
	virtual float CalculateCurrentWeaponAngle(float DeltaTime) override;
};
