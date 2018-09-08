// Christopher Laganella - Ramapo College of New Jersey senior project

#include "RTS_AttackingUnit.h"
#include "Runtime/Engine/Classes/Components/SphereComponent.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"


ARTS_AttackingUnit::ARTS_AttackingUnit()
{
	// Setup attack trigger around unit
	m_AttackTrigger = CreateDefaultSubobject<USphereComponent>("AttackTrigger");
	m_AttackTrigger->SetupAttachment(RootComponent);
	m_AttackTrigger->SetSphereRadius(m_Stats->Range, true);
	m_AttackTrigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	m_AttackTrigger->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel2);

	m_TargetTeamColor = ETeamColor::NONE;
	m_IsAttackMoving = false;
	m_IsAttackingTarget = false;
}

void ARTS_AttackingUnit::AttackMove(const FVector &a_Location)
{
	m_IsAttackMoving = true;
	m_IsAttackingTarget = false;

	// Doesn't reset flags like this verion will
	Super::MoveTo(a_Location);
}

void ARTS_AttackingUnit::AttackTargetUnit(ARTS_Unit *a_TargetUnit)
{
	m_IsAttackMoving = false;
	m_IsAttackingTarget = true;
	m_TargetUnit = a_TargetUnit;

	// Doesn't reset flags like this version does
	ARTS_Unit::MoveTo(a_TargetUnit->GetActorLocation());
}

void ARTS_AttackingUnit::MoveTo(const FVector &a_Location)
{
	m_IsAttackMoving = false;
	m_IsAttackingTarget = false;
	ARTS_Unit::MoveTo(a_Location);
}

void ARTS_AttackingUnit::Attack()
{
	// VIRTUAL FUNCTION - SHOULD NEVER EXECUTE HERE
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString(TEXT("Attacking ") + m_TargetedUnits[0]->GetName()));
	}
}

void ARTS_AttackingUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// If the unit is attacking
	if (m_IsAttackMoving)
	{
		TickAttackMove();
	}

	if (m_IsAttackingTarget)
	{
		TickAttackTarget();
	}
}

void ARTS_AttackingUnit::TickAttackMove()
{
	m_OverlappingActors.Empty();
	m_TargetedUnits.Empty();

	m_AttackTrigger->GetOverlappingActors(m_OverlappingActors, TSubclassOf<ARTS_Unit>());

	ARTS_Unit *tempUnit = nullptr;

	for (int i = 0; i < m_OverlappingActors.Num(); i++)
	{
		// UE4 elevates warming C4706 to an error and wont compile, why!?!?!?!?!?!?
		tempUnit = Cast<ARTS_Unit>(m_OverlappingActors[i]);
		if (tempUnit)
		{
			// This is basically &&?? test this idea somewhere else before condensing
			if (tempUnit->GetTeamColor() == m_TargetTeamColor)
			{
				m_TargetedUnits.Add(tempUnit);
			}
		}
	}

	if (m_TargetedUnits.Num() == 0)
	{
		// Do nothing because this is called by Tick()
		return;
	}
	else
	{
		StopMoving();
		Attack();
		ARTS_Unit::MoveTo(m_MoveLocation);
	}

}

void ARTS_AttackingUnit::TickAttackTarget()
{
	// Make init function ??
	m_OverlappingActors.Empty();
	m_TargetedUnits.Empty();

	m_AttackTrigger->GetOverlappingActors(m_OverlappingActors, TSubclassOf<ARTS_Unit>());

	ARTS_Unit *tempUnit = nullptr;

	for (int i = 0; i < m_OverlappingActors.Num(); i++)
	{
		tempUnit = Cast<ARTS_Unit>(m_OverlappingActors[i]);
		if (tempUnit)
		{
			if (tempUnit == m_TargetUnit)
			{
				m_TargetedUnits.EmplaceAt(0,tempUnit);
				break;
			}
		}
	}

	// Chase down the target if not currently in range
	if (m_TargetedUnits.Num() == 0)
	{
		Super::MoveTo(m_TargetUnit->GetActorLocation());
	}
	else
	{
		StopMoving();
		Attack();
		ARTS_Unit::MoveTo(m_MoveLocation);
	}
}