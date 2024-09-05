#include "Gameplay/WheeledRobotPawn.h"
#include "Gameplay/ReaperPawn.h"
#include "Net/UnrealNetwork.h"
#include "Gameplay/BattleRobotState.h"

AWheeledRobotPawn::AWheeledRobotPawn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bReplicates = 1;
	bAlwaysRelevant = 1;
}

float AWheeledRobotPawn::CalculateCurrentWeaponAngle(float DeltaTime)
{
	return 0.f;
}

void AWheeledRobotPawn::HandleStartWeaponInput()
{
	mWeaponState = RobotWeaponState::Active;

	if (!HasAuthority())
	{
		ServerHandleWeaponStateChanged(mWeaponState);
	}
}

void AWheeledRobotPawn::HandleEndWeaponInput()
{
	mWeaponState = RobotWeaponState::Inactive;

	if (!HasAuthority())
	{
		ServerHandleWeaponStateChanged(mWeaponState);
	}
}

void AWheeledRobotPawn::HandleToggleWeaponInput()
{
	if (mWeaponState == RobotWeaponState::Inactive)
	{
		mWeaponState = RobotWeaponState::Active;
	}
	else
	{
		mWeaponState = RobotWeaponState::Inactive;
	}

	if (!HasAuthority())
	{
		ServerHandleWeaponStateChanged(mWeaponState);
	}
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

	if (AReaperPawn* ReaperRobot = Cast<AReaperPawn>(AttackerRobot))
	{
		if (!ReaperRobot->CheckHitAvailable())
		{
			return;
		}
	}

	if (HasAuthority())
	{
		mCurrentHealth -= AttackerRobot->GetWeaponHitDamage();
		OnRep_CurrentHealth();

		ABattleRobotState* AttackerRobotState = Cast<ABattleRobotState>(AttackerRobot->GetPlayerState());
		AttackerRobotState->AddScore(AttackerRobot->GetWeaponHitDamage());
	}

	AttackerRobot->TriggerWeaponFX(HitLocation);
}

void AWheeledRobotPawn::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		mCurrentHealth = mStartingHealth;
		//Client not ready, comment this problem and how it was solved in doc, helper sync var
		//OnRep_CurrentHealth();
	}

	UpdateHealthUI();
}

void AWheeledRobotPawn::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AWheeledRobotPawn, mCurrentHealth);
	DOREPLIFETIME(AWheeledRobotPawn, mWeaponState);
}

void AWheeledRobotPawn::OnRep_CurrentHealth()
{
	if (!IsValid(this))
	{
		return;
	}

	UpdateHealthUI();
}

void AWheeledRobotPawn::ServerHandleWeaponStateChanged_Implementation(RobotWeaponState state)
{
	if (HasAuthority())
	{
		mWeaponState = state;
	}
}
