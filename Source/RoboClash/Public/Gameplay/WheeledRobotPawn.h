#pragma once

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "WheeledRobotPawn.generated.h"

UENUM()
enum class RobotWeaponState : uint8
{
	Inactive, 
	Active, 
	Count,
	Invalid
};

UCLASS()
class ROBOCLASH_API AWheeledRobotPawn : public AWheeledVehiclePawn
{
	GENERATED_BODY()

protected:
	RobotWeaponState mWeaponState = RobotWeaponState::Active;
	float mCurrentWeaponAngle = 0.f;

public:
	UFUNCTION(BlueprintCallable)
	virtual float CalculateCurrentWeaponAngle(float DeltaTime);
};