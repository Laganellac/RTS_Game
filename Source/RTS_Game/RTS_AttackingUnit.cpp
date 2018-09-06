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
	m_IsAttackingMoving = false;
}

void ARTS_AttackingUnit::AttackMove(FVector &a_Location)
{
	m_IsAttackingMoving = true;
	Move(a_Location);
}

void ARTS_AttackingUnit::AttackTargetUnit(ARTS_Unit *a_TargetUnit)
{
	m_IsAttackingMoving = false;
	TArray<AActor *> overlappingActors;
	m_AttackTrigger->GetOverlappingActors(overlappingActors, TSubclassOf<ARTS_Unit>());

	for (int i = 0; i < overlappingActors.Num(); i++)
	{
		// If the unit is in range then put make it a targeted unit
		if (a_TargetUnit == Cast<ARTS_Unit>(overlappingActors[i]))
		{
			m_TargetedUnits[0] = a_TargetUnit;
			break;
		}
	}
}

void ARTS_AttackingUnit::Attack()
{
	// VIRTUAL FUNCTION - SHOULD NEVER EXECUTE HERE
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Attacking %d"), m_TargetedUnits[0]));
	}
}

void ARTS_AttackingUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// If the unit is attacking
	if (m_IsAttackingMoving)
	{
		m_OverlappingActors.Empty();
		m_TargetedUnits.Empty();
		m_AttackTrigger->GetOverlappingActors(m_OverlappingActors, TSubclassOf<ARTS_Unit>());
		
		for (int i = 0; i < m_OverlappingActors.Num(); i++)
		{
			if (((ARTS_Unit *)m_OverlappingActors[i])->GetTeamColor() == m_TargetTeamColor)
			{
				m_TargetedUnits.Add((ARTS_Unit *)m_OverlappingActors[i]);
			}
		}

		if (m_TargetedUnits.Num() == 0)
		{
			
		}
		else
		{
			Attack();
		}
		
	}
}