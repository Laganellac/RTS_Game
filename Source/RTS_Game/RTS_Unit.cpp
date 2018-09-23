// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS_Unit.h"
#include "RTS_BuffingUnit.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"
#include "Runtime/Engine/Classes/AI/Navigation/NavigationSystem.h"

// Sets default values
ARTS_Unit::ARTS_Unit()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_SelectionIndicator = CreateDefaultSubobject<UStaticMeshComponent>("SelectedIndicator");
	m_SelectionIndicator->SetupAttachment(GetMesh());
	m_SelectionIndicator->SetVisibility(true);

	m_Stats.UnitName = EUnitName::NONE;
}

// Called when the game starts or when spawned
void ARTS_Unit::BeginPlay()
{
	Super::BeginPlay();
	m_SelectionIndicator->SetVisibility(false);
	m_Stats.CurrentHealth = m_Stats.TotalHealth;
	m_Stats.CurrentEnergy = m_Stats.TotalEnergy;
}

void ARTS_Unit::Die()
{
	Destroy();
}

void ARTS_Unit::MoveTo(const FVector &a_Location)
{
	m_MoveLocation = a_Location;
	Move();
}

EAttackResult ARTS_Unit::RecieveDamage(ARTS_Unit *a_Source, const float &a_Damage)
{
	// The potential result after taking damage or healing
	float potentialHealth = m_Stats.CurrentHealth - a_Damage;

	if (potentialHealth >= m_Stats.TotalHealth)
	{
		m_Stats.CurrentHealth = m_Stats.TotalHealth;
	}
	else
	{
		m_Stats.CurrentHealth = potentialHealth;

		if (IsDead())
		{
			Die();
			return EAttackResult::DEAD;
		}
	}
	return EAttackResult::ALIVE;
}

// Called every frame
void ARTS_Unit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARTS_Unit::SetSelected()
{
	m_SelectionIndicator->SetVisibility(true);
}

void ARTS_Unit::SetDeselected()
{
	m_SelectionIndicator->SetVisibility(false);
}

FRTS_UnitStats * ARTS_Unit::GetUnitStatsForBuff(ARTS_BuffingUnit * a_BuffingUnit)
{
	if (Cast<ARTS_BuffingUnit>(a_BuffingUnit))
	{
		return &m_Stats;
	}
	return nullptr;
}

void ARTS_Unit::Move()
{
	if (m_Stats.Speed <= 0.f)
	{
		return;
	}

	UNavigationSystem::SimpleMoveToLocation(this->GetController(), m_MoveLocation);
}

void ARTS_Unit::StopMoving()
{
	UNavigationSystem::SimpleMoveToLocation(this->GetController(), this->GetActorLocation());
}
