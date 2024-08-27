// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "RoboClashGameInstance.generated.h"


UCLASS()
class ROBOCLASH_API URoboClashGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(Transient, BlueprintReadWrite)
	FName ChosenRobotName;
	
};
