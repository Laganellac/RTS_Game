// Christopher Laganella - Ramapo College of New Jersey senior project

#include "RTS_AttackingUnit.h"
#include "Runtime/Engine/Classes/Components/SphereComponent.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "Runtime/Engine/Public/TimerManager.h"

/**
* Constructs an attacking unit and sets up the components. 
* 
*/
ARTS_AttackingUnit::ARTS_AttackingUnit()
{
	// Setup attack trigger around unit
	m_AttackTrigger = CreateDefaultSubobject<USphereComponent>("AttackTrigger");
	m_AttackTrigger->SetupAttachment(RootComponent);
	m_AttackTrigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	m_AttackTrigger->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel2);

	m_IsAttackMoving = false;
	m_IsAttackingTarget = false;

	/*
	m_TargetTeamColor = ETeamColor::NONE;
	m_Stats.UnitName = EUnitName::NONE;
	*/
}


/**
* Set's member flags so that the unit knows its "attack moving" then calls Super::MoveTo(a_Location)
* @param a_Location const FVector& - The location to move to
*/
void ARTS_AttackingUnit::AttackMove(const FVector &a_Location)
{
	m_IsAttackMoving = true;
	m_IsAttackingTarget = false;

	// Doesn't reset flags like this verion will
	Super::MoveTo(a_Location);
}

/**
* Set's member flags so that the uni knows to chase down the target. Sets m_TargetUnit to a_TargetUnit
* @param a_TargetUnit ARTS_Unit * - The unit to attack
*/
void ARTS_AttackingUnit::AttackTargetUnit(ARTS_Unit *a_TargetUnit)
{
	m_IsAttackMoving = false;
	m_IsAttackingTarget = true;

	if (a_TargetUnit == this)
	{
		// Attack moves in place
		AttackMove(GetActorLocation());
	}
	else
	{
		// Doesn't reset flags like this version does
		m_TargetUnit = a_TargetUnit;
		ARTS_Unit::MoveTo(a_TargetUnit->GetActorLocation());
	}

}

/**
* Sets member flags so that the unit knows not to attack then calls ARTS_Unit::MoveTo(a_Location)
* @param a_Location const FVector& - The location to move to
*/
void ARTS_AttackingUnit::MoveTo(const FVector &a_Location)
{
	m_IsAttackMoving = false;
	m_IsAttackingTarget = false;
	ARTS_Unit::MoveTo(a_Location);
}

/**
* Overrides the ARTS_Unit version. First calls the ARTS_Unit version then sets the m_TargetTeamColor to the opposite team
* @param a_TeamColor ETeamColor - The this units new team color
*/
void ARTS_AttackingUnit::SetTeamColor(ETeamColor a_TeamColor)
{
	ARTS_Unit::SetTeamColor(a_TeamColor);

	if (a_TeamColor == ETeamColor::BLUE)
	{
		m_TargetTeamColor = ETeamColor::RED;
	}

	else if (a_TeamColor == ETeamColor::RED)
	{
		m_TargetTeamColor = ETeamColor::BLUE;
	}

	else
	{
		m_TargetTeamColor = ETeamColor::NONE;
	}
}

/**
* Attacks the unit stored in m_TargetUnits[0] and outputs the result to the screen (virtual)
*/
void ARTS_AttackingUnit::Attack()
{
	// Can't attack faster than attack speed
	if (GetWorldTimerManager().IsTimerActive(m_AttackLockoutTimer))
	{
		return;
	}

	EAttackResult result;
	GetWorldTimerManager().SetTimer(m_AttackLockoutTimer, m_Stats.AttackSpeed, false);

	result = m_TargetedUnits[0]->RecieveDamage(this, m_Stats.Damage);

	if (result == EAttackResult::DEAD)
	{

		AttackMove(GetActorLocation());
	}

	

	// For debugging purposes
	if (GEngine)
	{
		if (m_Stats.TeamColor == ETeamColor::BLUE)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString(this->GetName() +  TEXT(" attacked ") + m_TargetedUnits[0]->GetName() + TEXT(", current health = ") + FString::SanitizeFloat(m_TargetedUnits[0]->GetCurrentHealth(), 1)));
		}
		else if (m_Stats.TeamColor == ETeamColor::RED)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString(this->GetName() + TEXT(" attacked ") + m_TargetedUnits[0]->GetName() + TEXT(", current health = ") + FString::SanitizeFloat(m_TargetedUnits[0]->GetCurrentHealth(), 1)));

		}
	}

	
}

/**
* Called when this unit is spawned. Sets the attack trigger's radius to this units range
*/
void ARTS_AttackingUnit::BeginPlay()
{
	Super::BeginPlay();

	m_AttackTrigger->SetSphereRadius(m_Stats.Range, true);
}

/**
*
*/
void ARTS_AttackingUnit::Move()
{
	ARTS_Unit::Move();
}

/**
* Overrides tick, Calls Super::Tick and then checks if this unit is attack moving or attacking target then calls the respective tick function
* @param DeltaTime float - A constant value defined by UE4 everytime the tick loop is started
*/
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

/**
* Checks for any units in range then checks if they are on the target team. If they are they will be added to m_TargetUnits
*/
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
			if (tempUnit->GetTeamColor() == m_TargetTeamColor && tempUnit != this)
			{
				m_TargetedUnits.Add(tempUnit);
			}
		}
	}

	if (m_TargetedUnits.Num() == 0)
	{
		// Do nothing because this is called by Tick()
		ARTS_Unit::MoveTo(m_MoveLocation);
		return;
	}
	else
	{
		StopMoving();
		Attack();
	}

}

/**
* Checks if m_TargetUnit is in range. If not it tries to acquire m_TargetUnit's location and moves there
*/
void ARTS_AttackingUnit::TickAttackTarget()
{
	// Make init function ??
	m_OverlappingActors.Empty();
	m_TargetedUnits.Empty();

	m_AttackTrigger->GetOverlappingActors(m_OverlappingActors);

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

	// Check if any units are still in range
	if (m_TargetedUnits.Num() == 0)
	{
		// If the target still exists go chase it
		if (m_TargetUnit->IsValidLowLevel())
		{
			ARTS_Unit::MoveTo(m_TargetUnit->GetActorLocation());
		}

		// If the target no longer exists just attack move in place
		else
		{

			AttackMove(GetActorLocation());
		}
	}
	else
	{
		StopMoving();
		Attack();
	}
}