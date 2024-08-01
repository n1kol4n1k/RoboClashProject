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

	UPROPERTY(EditAnywhere)
	FName mWeaponBoneName;

	UPROPERTY(EditAnywhere)
	float mStartingHealth;
	
	UPROPERTY(EditAnywhere) //move to transient after implementing ui
	float mCurrentHealth;

	UPROPERTY(EditAnywhere)
	float mWeaponHitDamage;

public:
	float GetWeaponHitDamage() const { return mWeaponHitDamage; }

	UFUNCTION(BlueprintCallable)
	virtual float CalculateCurrentWeaponAngle(float DeltaTime);

	UFUNCTION(BlueprintCallable)
	void HandleStartWeaponInput();

	UFUNCTION(BlueprintCallable)
	void HandleEndWeaponInput();

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateHealthUI(float CurrHealth, float CurrHealthPercentage);

	virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;
	virtual void BeginPlay() override;
};