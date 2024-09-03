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

public:
	AWheeledRobotPawn(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(Transient, Replicated)
	RobotWeaponState mWeaponState = RobotWeaponState::Inactive;

	float mCurrentWeaponAngle = 0.f;

	UPROPERTY(EditAnywhere)
	FName mWeaponBoneName;

	UPROPERTY(EditAnywhere)
	float mStartingHealth;
	
	UPROPERTY(Transient, ReplicatedUsing=OnRep_CurrentHealth)
	float mCurrentHealth;

	UPROPERTY(EditAnywhere)
	float mWeaponHitDamage;

	void UpdateHealthUI() { UpdateHealthUI(mCurrentHealth, mCurrentHealth / mStartingHealth); }

public:
	float GetWeaponHitDamage() const { return mWeaponHitDamage; }
	RobotWeaponState GetWeaponState() const { return mWeaponState; }
	const FName& GetWeaponBoneName() const { return mWeaponBoneName; }

	UFUNCTION(BlueprintCallable)
	virtual float CalculateCurrentWeaponAngle(float DeltaTime);

	UFUNCTION(BlueprintCallable)
	void HandleStartWeaponInput();

	UFUNCTION(BlueprintCallable)
	void HandleEndWeaponInput();

	UFUNCTION(BlueprintCallable)
	virtual void HandleToggleWeaponInput();

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateHealthUI(float CurrHealth, float CurrHealthPercentage);

	UFUNCTION(BlueprintImplementableEvent)
	void TriggerWeaponFX(FVector HitLocation);

	virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
	UFUNCTION()
	void OnRep_CurrentHealth();

	UFUNCTION(Server, Reliable)
	void ServerHandleWeaponStateChanged(RobotWeaponState state);
	void ServerHandleWeaponStateChanged_Implementation(RobotWeaponState state);
};