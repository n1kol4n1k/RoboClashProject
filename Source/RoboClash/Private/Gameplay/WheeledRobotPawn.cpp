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
	//Damaged robot calls this

	AWheeledRobotPawn* AttackerRobot = Cast<AWheeledRobotPawn>(Other);
	if (AttackerRobot == nullptr
		|| AttackerRobot->GetWeaponState() == RobotWeaponState::Inactive
		|| AttackerRobot->GetWeaponBoneName() != Hit.BoneName)
	{
		return;
	}


	mCurrentHealth -= AttackerRobot->GetWeaponHitDamage();
	AttackerRobot->TriggerWeaponFX(HitLocation);
	UpdateHealthUI();
}

void AWheeledRobotPawn::BeginPlay()
{
	Super::BeginPlay();

	mCurrentHealth = mStartingHealth;
	UpdateHealthUI();
}
