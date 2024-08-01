#include "Gameplay/WheeledRobotPawn.h"

float AWheeledRobotPawn::CalculateCurrentWeaponAngle(float DeltaTime)
{
	return 0.f;
}

void AWheeledRobotPawn::HandleStartWeaponInput()
{
	mWeaponState = RobotWeaponState::Active;
}

void AWheeledRobotPawn::HandleEndWeaponInput()
{
	mWeaponState = RobotWeaponState::Inactive;
}

void AWheeledRobotPawn::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	if (mWeaponState == RobotWeaponState::Inactive)
	{
		return;
	}

	if (Hit.BoneName != mWeaponBoneName)
	{
		return;
	}

	if (AWheeledRobotPawn* OtherRobot = Cast<AWheeledRobotPawn>(Other))
	{
		mCurrentHealth -= OtherRobot->GetWeaponHitDamage();
		UpdateHealthUI(mCurrentHealth, mCurrentHealth / mStartingHealth);
		OtherRobot->TriggerWeaponFX(HitLocation);
	}
}

void AWheeledRobotPawn::BeginPlay()
{
	Super::BeginPlay();

	mCurrentHealth = mStartingHealth;
	UpdateHealthUI(mCurrentHealth, mCurrentHealth/mStartingHealth);
}
