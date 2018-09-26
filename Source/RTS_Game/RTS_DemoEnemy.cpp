// Christopher Laganella - Ramapo College of New Jersey senior project

#include "RTS_DemoEnemy.h"
#include "RTS_Unit.h"
#include "RTS_BlueprintRefs.h"
#include "RTS_CapturePoint.h"
#include "RTS_PlayerController.h"
#include "RTS_AttackingUnit.h"
#include "Runtime/Engine/Classes/Components/CapsuleComponent.h"
#include "Runtime/Engine/Classes/Engine/World.h"

URTS_DemoEnemy::URTS_DemoEnemy()
{
	m_BlueprintRefs = NewObject<URTS_BlueprintRefs>();
}

void URTS_DemoEnemy::ArmyAttack()
{
	
	// If this is on defense
	if (m_TeamColor == ETeamColor::BLUE)
	{
		ARTS_AttackingUnit *attackingUnitCast;
		FVector attackLocation;
		for (int i = 0; i < m_Units.Num(); i++)
		{
			attackingUnitCast = Cast<ARTS_AttackingUnit>(m_Units[i]);
			if (attackingUnitCast->IsValidLowLevel())
			{
				// Turn the units to face the player
				attackLocation = attackingUnitCast->GetActorLocation() + FVector(-50.f, 0.f, 0.f);
				attackingUnitCast->AttackMove(attackLocation);
			}
			// If the unit wasn't an attacking unit just do nothing (it can sit in place)
			else
			{

			}
		}
	}
	// If its not on defense then its on offense
	else
	{
		ARTS_AttackingUnit *attackingUnitCast;
		ARTS_AttackingUnit *swordsman = nullptr;
		for (int i = 0; i < m_Units.Num(); i++)
		{
			attackingUnitCast = Cast<ARTS_AttackingUnit>(m_Units[i]);
			if (attackingUnitCast->IsValidLowLevel())
			{
				attackingUnitCast->AttackMove(m_EnemyCapturePointLoc);
				
				// If its a swordsman store its reference so the one of the healers can heal it
				if (attackingUnitCast->GetUnitName() == EUnitName::SWORDSMAN)
				{
					swordsman = attackingUnitCast;
				}

				// If it's a healer have it chase one of the swordsmen
				else if (attackingUnitCast->GetUnitName() == EUnitName::HEALER)
				{
					if (swordsman->IsValidLowLevel())
					{
						attackingUnitCast->AttackTargetUnit(swordsman);
					}
				}
			}
			// If this isnt an attacking unit (basically if its a general)
			else
			{
				// Just run it down mid
				m_Units[i]->MoveTo(m_EnemyCapturePointLoc);
			}
		}
	
	}
}

void URTS_DemoEnemy::Construct(ARTS_PlayerController *a_OwningController, ARTS_CapturePoint * a_CapturePoint, const FVector &a_EnemySpawnLoc)
{
	// The player that owns this
	m_OwningController = a_OwningController;

	// Spawn the enemy 1000 units infront of the camera, the camera is 100 units off the ground
	m_SpawnLocationBase = a_EnemySpawnLoc + FVector(1200.f, 0.f, -100.f);

	

	// Then the player is on attack, which means this is defending
	if (a_CapturePoint == nullptr)
	{
		m_TeamColor = ETeamColor::BLUE;
		
	}
	// Then the player must be on defense, which means this is attacking
	else
	{
		m_TeamColor = ETeamColor::RED;
		m_EnemyCapturePointLoc = a_CapturePoint->GetActorLocation();
	}
	
	InitializeArmyList();
}

void URTS_DemoEnemy::InitializeArmyList()
{
	// If this is on defense
	if (m_TeamColor == ETeamColor::BLUE)
	{
		m_ArmyList.Add(EUnitName::SWORDSMAN);
		m_ArmyList.Add(EUnitName::DEFENSE_TOWER);
		m_ArmyList.Add(EUnitName::SWORDSMAN);
		m_ArmyList.Add(EUnitName::ARCHER);
		m_ArmyList.Add(EUnitName::SWORDSMAN);
		m_ArmyList.Add(EUnitName::DEFENSE_TOWER);
	}
	// If this isnt on defense its on offense
	else
	{
		m_ArmyList.Add(EUnitName::GENERAL);
		m_ArmyList.Add(EUnitName::HEALER);
		m_ArmyList.Add(EUnitName::SWORDSMAN);
		m_ArmyList.Add(EUnitName::ARCHER);
		m_ArmyList.Add(EUnitName::SWORDSMAN);
		m_ArmyList.Add(EUnitName::HEALER);
	}
}

void URTS_DemoEnemy::SpawnArmy()
{
	if (m_TeamColor == ETeamColor::BLUE)
	{
		ARTS_CapturePoint *capturePointCast = Cast<ARTS_CapturePoint>(m_OwningController->GetWorld()->SpawnActor(ARTS_CapturePoint::StaticClass(), &m_SpawnLocationBase));
		// Cast returns 0 if invalid cast
		if (capturePointCast->IsValidLowLevel())
		{
			capturePointCast->OnChanged().AddUObject(m_OwningController, &ARTS_PlayerController::OnPointCapture);
			capturePointCast->SetTeamColor(ETeamColor::BLUE);
			//capturePointCast->StartTimerTick();
		}
	}

	UClass *blueprintClass;
	ARTS_Unit *unitCast;
	FVector spawnLocation;
	FVector tempLocation(0.f, 0.f, 2000.f);
	float halfHeight;
	for (int i = 0; i < m_ArmyList.Num(); i++)
	{
		
		blueprintClass = m_BlueprintRefs->GetBlueprintClass(m_ArmyList[i]);
		unitCast = Cast<ARTS_Unit>(m_OwningController->GetWorld()->SpawnActor(blueprintClass, &tempLocation));

		if (unitCast->IsValidLowLevel())
		{
			// ALL units have a CapsuleComponent as their root so this should be safe
			UCapsuleComponent *capsule = (UCapsuleComponent *)unitCast->GetRootComponent();
			halfHeight = capsule->GetScaledCapsuleHalfHeight();
			spawnLocation = m_SpawnLocationBase + FVector(i % 2 * 200 + 100, i % 3 * 200 - 200, halfHeight);

			unitCast->SetTeamColor(m_TeamColor);
			unitCast->GetRootComponent()->SetWorldLocation(spawnLocation);
			m_Units.Add(unitCast);
		}
		// If it failed to spawn do it again
		else
		{
			i--;
		}
	}
}

int URTS_DemoEnemy::GetNumAlive()
{
	for (int i = 0; i < m_Units.Num(); i++)
	{
		if (m_Units[i]->IsValidLowLevel())
		{

		}
		else
		{
			m_Units.RemoveAt(i, 1, false);
		}
	}
	m_Units.Shrink();
	return m_Units.Num();
}
