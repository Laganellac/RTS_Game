// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS_Unit.h"
#include "RTS_BuffingUnit.h"
#include "Runtime/Engine/Classes/Components/SpotLightComponent.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"
#include "Runtime/Engine/Classes/AI/Navigation/NavigationSystem.h"

/**
* Sets default values and creates components
*/
ARTS_Unit::ARTS_Unit()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_SelectionIndicator = CreateDefaultSubobject<UStaticMeshComponent>("SelectedIndicator");
	m_SelectionIndicator->SetupAttachment(GetMesh());
	m_SelectionIndicator->SetVisibility(true);

	m_ColorLight = CreateDefaultSubobject<USpotLightComponent>("ColorLight");
	m_ColorLight->SetupAttachment(GetMesh());
	m_ColorLight->SetVisibility(true);

	m_Stats.UnitName = EUnitName::NONE;
}

/**
* Called when spawned. Makes selection indicator invisible. Makes it so the unit has full health and energy
*/
void ARTS_Unit::BeginPlay()
{
	Super::BeginPlay();
	m_SelectionIndicator->SetVisibility(false);
	m_Stats.CurrentHealth = m_Stats.TotalHealth;
	m_Stats.CurrentEnergy = m_Stats.TotalEnergy;
}

/**
* Marks this unit for destruction
*/
void ARTS_Unit::Die()
{
	Destroy();
}

/**
* Sets m_MoveLocation then calls move
* @param a_Location const FVector & - The location to move to
*/
void ARTS_Unit::MoveTo(const FVector &a_Location)
{
	m_MoveLocation = a_Location;
	Move();
}

/**
* Checks if the given unit is on the player's team
* @param a_Source ARTS_Unit * - The unit that attacked  this unit
* @param a_Damage const float & - The amount of damage to take
* @return EAttackResult - Whether this unit died or not
*/
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

/**
* Called every frame
*/
void ARTS_Unit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/**
* Setter for m_TeamColor
* @param a_TeamColor ETeamColor - The new team color
*/
void ARTS_Unit::SetTeamColor(ETeamColor a_TeamColor)
{
	m_Stats.TeamColor = a_TeamColor;

	if (a_TeamColor == ETeamColor::BLUE)
	{
		m_ColorLight->SetLightColor(FLinearColor::Blue);
	}

	else if (a_TeamColor == ETeamColor::RED)
	{
		m_ColorLight->SetLightColor(FLinearColor::Red);
	}

	else
	{
		m_ColorLight->SetLightColor(FLinearColor::Black);
	}
}

/**
* Makes the selection indicator visible
*/
void ARTS_Unit::SetSelected()
{
	m_SelectionIndicator->SetVisibility(true);
}

/**
* Makes the selection indicator invisible
*/
void ARTS_Unit::SetDeselected()
{
	m_SelectionIndicator->SetVisibility(false);
}

/**
* Checks if a buffing unit is calling this function
* @param a_BuffingUnit ARTS_BuffingUnit * - The buffing unit calling this function
* @return FRTS_UnitStats -  A reference to this unit's m_Stats OR nullptr if called by non ARTS_BuffingUnit
*/
FRTS_UnitStats * ARTS_Unit::GetUnitStatsForBuff(ARTS_BuffingUnit * a_BuffingUnit)
{
	if (Cast<ARTS_BuffingUnit>(a_BuffingUnit))
	{
		return &m_Stats;
	}
	return nullptr;
}

/**
* Moves this unit to m_MoveLocation if the unit is allowed to move
*/
void ARTS_Unit::Move()
{
	if (m_Stats.Speed <= 0.f)
	{
		return;
	}

	UNavigationSystem::SimpleMoveToLocation(this->GetController(), m_MoveLocation);
}

/**
* Tells the unit to stop moving
*/
void ARTS_Unit::StopMoving()
{
	UNavigationSystem::SimpleMoveToLocation(this->GetController(), this->GetActorLocation());
}
