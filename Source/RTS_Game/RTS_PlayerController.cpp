// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS_PlayerController.h"
#include "RTS_HUD.h"
#include "RTS_Unit.h"
#include "RTS_AttackingUnit.h"
#include "RTS_BlueprintRefs.h"
#include "RTS_CapturePoint.h"
#include "RTS_CameraPawn.h"
#include "RTS_DemoEnemy.h"
#include "Runtime/Engine/Classes/Components/CapsuleComponent.h"
#include "Runtime/Engine/Classes/AI/Navigation/NavigationSystem.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"
#include "Runtime/Engine/Classes/Engine/World.h"

ARTS_PlayerController::ARTS_PlayerController()
{
	// Member variables of parent class
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Hand;

	m_Stats.CurrentGold = 1000;
	// Member variables of this class
	m_GroupingUnits = false;
	m_MustSpawnPoint = false;
	m_PlacingUnits = false;
	m_Paused = false;
	m_RoundStarted = false;

	m_BlueprintRefs = NewObject<URTS_BlueprintRefs>();
	m_CapturePoint = nullptr;
	
	//NewObject<URTS_BlueprintRefs>(m_BlueprintRefs, URTS_BlueprintRefs::StaticClass());
}

void ARTS_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	m_CurrentHUD = Cast<ARTS_HUD>(GetHUD());

	// Make sure this is empty at the start
	m_SelectedUnits.Empty();
}

void ARTS_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("LeftMouseClick", IE_Pressed, this, &ARTS_PlayerController::SelectionPressed);

	InputComponent->BindAction("RightMouseClick", IE_Released, this, &ARTS_PlayerController::MovePressed);

	InputComponent->BindAction("GroupUnits", IE_Pressed, this, &ARTS_PlayerController::GroupUnitsPressed);
	InputComponent->BindAction("GroupUnits", IE_Released, this, &ARTS_PlayerController::GroupUnitsReleased);

	InputComponent->BindAction("Attack", IE_Pressed, this, &ARTS_PlayerController::AttackPressed);

	InputComponent->BindAction("Exit", IE_Pressed, this, &ARTS_PlayerController::ExitPressed);
	InputComponent->BindAction("Reset", IE_Pressed, this, &ARTS_PlayerController::RestartPressed);
}

void ARTS_PlayerController::Tick(float a_DeltaTime)
{

	if (m_DemoEnemy->IsValidLowLevel())
	{
		// If all the enemy's units are dead you win
		if (!m_DemoEnemy->GetNumAlive())
		{
			m_CurrentHUD->EndRound(m_Stats.TeamColor);
		}
	}

	if (m_RoundStarted)
	{
		// If all your units are dead you lose
		if (!GetNumAlive())
		{
			if (m_Stats.TeamColor == ETeamColor::RED)
			{
				m_CurrentHUD->EndRound(ETeamColor::BLUE);
			}
			else if (m_Stats.TeamColor == ETeamColor::BLUE)
			{
				m_CurrentHUD->EndRound(ETeamColor::RED);
			}
		}

	}
	// If we are currently making a selection box
	//if (m_Selecting)
	//{


		// Code for making a 3D selection box
		//FHitResult hit;
		//GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel1, false, hit);
		////DrawDebugSphere(GetWorld(), hit.Location, 25, 10, FColor::Yellow, false, 3.f);

		//// Calculate and store the center of the line created by our two points
		//FVector selectionRectCenter = FVector(  (m_InitialSelectionClick.Location.X + hit.Location.X) / 2.f,
		//										(m_InitialSelectionClick.Location.Y + hit.Location.Y) / 2.f, 100.f);

		//// Calculate and store the "extent" of the rectangle we wish to create by using our two points
		//FVector selectionRectExtents = FVector(  fabsf(hit.Location.X - selectionRectCenter.X),
		//										 fabsf(hit.Location.Y - selectionRectCenter.Y), 100.f);

		////ARTS_SelectionBox selectionBox(selectionRectExtents);
		////GetWorld()->SpawnActor<ARTS_SelectionBox>((UClass *)&selectionBox, selectionRectCenter, FRotator(0,0,0));
		//
		////DrawDebugBox(GetWorld(), selectionRectCenter, selectionRectExtents, FColor::Red, true, 2.f);
	//}
}

void ARTS_PlayerController::AddUnit(EUnitName a_UnitName)
{
	FRTS_UnitStats tempUnitStats = URTS_Lib::GetUnitStats(a_UnitName);

	m_PurchasedUnits.Add(tempUnitStats.UnitName);
	m_Stats.CurrentGold -= tempUnitStats.Cost;
	
}

void ARTS_PlayerController::OnPointCapture()
{
	m_CurrentHUD->EndRound(ETeamColor::RED);
}

void ARTS_PlayerController::StartRound()
{
	// If this player is on defense
	if (m_Stats.TeamColor == ETeamColor::BLUE)
	{
		m_MustSpawnPoint = true;
	}

	// If no units were purchased restart the game because thats invalid
	if (!m_PurchasedUnits.Num())
	{
		RestartPressed();
	}
	m_PlacingUnits = true;
}

ARTS_Unit * ARTS_PlayerController::GetSelectedUnit()
{
	if (m_SelectedUnits.Num())
	{
		return m_SelectedUnits[0];
	}
	return nullptr;
}

EUnitName ARTS_PlayerController::GetNextUnitToSpawn()
{
	// If the capture point hasnt been spawned then it will be the first thing on the list
	if (m_MustSpawnPoint)
	{
		return EUnitName::POINT;
	}

	
	// If there are units still in the array returnt the one that will be popped
	if (m_PurchasedUnits.Num())
	{
		return m_PurchasedUnits.Last();
	}
	

	// If there are no units left return NONE
	return EUnitName::NONE;
}

int ARTS_PlayerController::GetNumAlive()
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

//30 min 9.6.18
void ARTS_PlayerController::Attack(FHitResult &a_Hit)
{
	// If the thing clicked is a unit use it as a target
	ARTS_Unit *targetedUnit = Cast<ARTS_Unit>(a_Hit.GetActor());
	if (targetedUnit)
	{
		for (int i = 0; i < m_SelectedUnits.Num(); i++)
		{
			ARTS_AttackingUnit *attacker = Cast<ARTS_AttackingUnit>(m_SelectedUnits[i]);
			if (attacker)
			{
				attacker->AttackTargetUnit(targetedUnit);
			}
		}
	}
	// If the thing clicked isnt a unit then attack move to the location
	else
	{
		FVector location = a_Hit.Location;
		for (int i = 0; i < m_SelectedUnits.Num(); i++)
		{
			ARTS_AttackingUnit *attacker = Cast<ARTS_AttackingUnit>(m_SelectedUnits[i]);
			if (attacker)
			{
				attacker->AttackMove(location);
			}
		}

	}
}

//1hour 9.6.18
void ARTS_PlayerController::AttackPressed()
{
	for (int i = 0; i < m_SelectedUnits.Num(); i++)
	{
		// Can only attack with attacking units; if there are any non attacking units remove them from the list
		if (Cast<ARTS_AttackingUnit>(m_SelectedUnits[i]))
		{
			// If m_Attacking hasnt already been set to true then it must be set, m_GroupingUnits should also be reset
			if (!m_Attacking)
			{
				m_GroupingUnits = false;
				m_Attacking = true;
			}
		}
		// Remove the item from the list but do not shrink it yet
		else
		{
			m_SelectedUnits[i]->SetDeselected();
			m_SelectedUnits.RemoveAt(i);
			i--;
		}
	}
}

// 10 min 8.28.18
void ARTS_PlayerController::DeselectUnits()
{
	for (int i = 0; i < m_SelectedUnits.Num(); i++)
	{
		m_SelectedUnits[i]->SetDeselected();
	}
	m_SelectedUnits.Empty();
}

// 5 min 8.30.18
bool ARTS_PlayerController::IsOnPlayerTeam(ARTS_Unit * a_Unit)
{
	if (m_Stats.TeamColor == a_Unit->GetTeamColor())
	{
		return true;
	}
	return false;
}

void ARTS_PlayerController::ExitPressed()
{
	// Exit the game
	FGenericPlatformMisc::RequestExit(false);
}

// 5 min 8.28.18
void ARTS_PlayerController::GroupUnitsPressed()
{
	m_GroupingUnits = true;
}

//5 min 8.28.18
void ARTS_PlayerController::GroupUnitsReleased()
{
	m_GroupingUnits = false;
}

// 1 hour 8.28.18
void ARTS_PlayerController::SelectionPressed()
{
	// Places the hitresult in hit
	FHitResult hit;
	GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel1, false, hit);
	//DrawDebugSphere(GetWorld(), hit.Location, 25, 10, FColor::Yellow, false, 20.f);

	if (m_PlacingUnits)
	{
		SpawnUnit(hit);
		return;
	}

	if (m_Attacking)
	{
		Attack(hit);
		m_Attacking = false;
		return;
	}

	// Empty the array of selected units if the player is not trying to group units
	if (!m_GroupingUnits)
	{
		DeselectUnits();
	}
	
	// Attempts to Cast AActor* to ARTS_Unit*, if unsuccessful nullptr is returned. If clickedUnit isnt a Unit return
	ARTS_Unit *clickedUnit = Cast<ARTS_Unit>(hit.GetActor());
	if (clickedUnit == nullptr)
	{
		return;
	}

	// Makes sure that you are only grouping a unit that is on your team into your selection
	if (m_GroupingUnits && !IsOnPlayerTeam(clickedUnit))
	{
		return;
	}

	//******check if this unit is on the same team
	if (m_Stats.TeamColor == clickedUnit->GetTeamColor())
	{
		clickedUnit->SetSelected();
		m_SelectedUnits.Add(clickedUnit);
	}

	
	// Used for selection boxes
	//m_Selecting = true;
}

void ARTS_PlayerController::SpawnUnit(FHitResult &a_Hit)
{
	// Do nothing if the player doesnt click on the ground
	if (a_Hit.Location.Z > 1.f)
	{
		return;
	}

	FVector spawnLocation = a_Hit.Location + FVector(0.f, 0.f, 100.f);

	if (m_MustSpawnPoint)
	{
		m_MustSpawnPoint = false;
		ARTS_CapturePoint *capturePointCast = Cast<ARTS_CapturePoint>(GetWorld()->SpawnActor(ARTS_CapturePoint::StaticClass(), &spawnLocation));
		// Cast returns 0 if invalid cast
		if (capturePointCast)
		{
			capturePointCast->OnChanged().AddUObject(this, &ARTS_PlayerController::OnPointCapture);
			capturePointCast->SetTeamColor(ETeamColor::BLUE);
			m_CapturePoint = capturePointCast; //REMOVE THIS LINE IN THE FUTURE - FOR DEMO ONLY!!!
		}
		else
		{
			m_MustSpawnPoint = true;
		}
		return;
	}

	FVector tempLocation = FVector(0, 0, -1000.f);

	// Pops unit out of the purchased units array
	EUnitName currentUnit = m_PurchasedUnits.Pop();
	UClass *blueprintClass = m_BlueprintRefs->GetBlueprintClass(currentUnit);
	ARTS_Unit *unitCast = Cast<ARTS_Unit>(GetWorld()->SpawnActor(blueprintClass, &tempLocation));
	float halfHeight;

	if (unitCast)
	{
		// ALL units have a CapsuleComponent as their root so this should be safe
		UCapsuleComponent *capsule = (UCapsuleComponent *)unitCast->GetRootComponent();
		halfHeight = capsule->GetScaledCapsuleHalfHeight();
		spawnLocation = spawnLocation + FVector(0.f, 0.f, halfHeight);
		
		unitCast->SetTeamColor(m_Stats.TeamColor);
		unitCast->GetRootComponent()->SetWorldLocation(spawnLocation);
		m_Units.Add(unitCast);
	}
	else
	{
		// If it failed to spawn here, add it back to the array
		m_PurchasedUnits.Add(currentUnit);
		return;
	}

	// If there are no purchased units left in the array
	if (!m_PurchasedUnits.Num())
	{
		m_PlacingUnits = false;
		// Nasty one-liner, safely cast Getpawn() to CameraPawn then tell it that its allowed to move
		if (Cast<ARTS_CameraPawn>(GetPawn())) Cast<ARTS_CameraPawn>(GetPawn())->SetCanMove(true);
		SpawnEnemies(); // MORE CODE FOR DEMO
		m_CurrentHUD->StartInGameHUD();
		m_RoundStarted = true;
	}
}

void ARTS_PlayerController::SpawnEnemies()
{
	m_DemoEnemy = NewObject<URTS_DemoEnemy>();
	m_DemoEnemy->Construct(this, m_CapturePoint, GetPawn()->GetActorLocation());
	m_DemoEnemy->SpawnArmy();
	m_DemoEnemy->ArmyAttack();
}

// 10 min 8.28.18
void ARTS_PlayerController::MovePressed()
{
	// Places the hitresult in hit
	FHitResult hit; 
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, hit);

	// Move all of the units to the new location
	for (int32 i = 0; i < m_SelectedUnits.Num(); i++)
	{
		FVector moveLocation = hit.Location + FVector(i / 2 * 100, i % 2 * 100, 0);
		// Make sure this unit still exists (it could've died)
		if (m_SelectedUnits[i]->IsValidLowLevel())
		{
			m_SelectedUnits[i]->MoveTo(moveLocation);
		}
		// Remove it if its dead
		else
		{
			m_SelectedUnits.RemoveAt(i, 1, false);
		}
		DrawDebugSphere(GetWorld(), moveLocation, 25, 10, FColor::Red, false, 0.2f);
	}
	m_SelectedUnits.Shrink();
}

void ARTS_PlayerController::RestartPressed()
{
	this->ConsoleCommand(TEXT("RestartLevel"));
}
