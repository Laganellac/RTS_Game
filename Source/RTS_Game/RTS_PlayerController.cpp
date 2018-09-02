// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS_PlayerController.h"
#include "RTS_HUD.h"
#include "RTS_Unit.h"
#include "Runtime/Engine/Classes/AI/Navigation/NavigationSystem.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"
#include "Runtime/Engine/Classes/Engine/World.h"

ARTS_PlayerController::ARTS_PlayerController()
{
	// Member variables of parent class
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Hand;

	// Member variables of this class
	m_GroupingUnits = false;

	m_Stats = new FRTS_PlayerStats;
}

// 5 min 9.1.18
ARTS_PlayerController::~ARTS_PlayerController()
{
	delete m_Stats;
}

void ARTS_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	m_CurrentHUD = Cast<ARTS_HUD>(GetHUD());

	// Ensure the the game isn't sta
	m_SelectedUnits.Empty();
}

void ARTS_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("LeftMouseClick", IE_Pressed, this, &ARTS_PlayerController::SelectionPressed);

	InputComponent->BindAction("RightMouseClick", IE_Released, this, &ARTS_PlayerController::MovePressed);

	InputComponent->BindAction("GroupUnits", IE_Pressed, this, &ARTS_PlayerController::GroupUnitsPressed);
	InputComponent->BindAction("GroupUnits", IE_Released, this, &ARTS_PlayerController::GroupUnitsReleased);
}

void ARTS_PlayerController::Tick(float a_DeltaTime)
{



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
	if (m_Stats->TeamColor == a_Unit->GetTeamColor())
	{
		return true;
	}
	return false;
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
	// Places the hitresult in m_InitialSelectionClick
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, m_InitialSelectionClick);
	DrawDebugSphere(GetWorld(), m_InitialSelectionClick.Location, 25, 10, FColor::Yellow, false, 20.f);

	// Empty the array of selected units if the player is not trying to group units
	if (!m_GroupingUnits)
	{
		DeselectUnits();
	}
	
	// Attempts to Cast AActor* to ARTS_Unit*, if unsuccessful nullptr is returned. If clickedUnit isnt a Unit return
	ARTS_Unit *clickedUnit = Cast<ARTS_Unit>(m_InitialSelectionClick.GetActor());
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

	clickedUnit->SetSelected();
	m_SelectedUnits.Add(clickedUnit);
	
	// Used for selection boxes
	//m_Selecting = true;
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
		FVector MoveLocation = hit.Location + FVector(i / 2 * 100, i % 2 * 100, 0);
		UNavigationSystem::SimpleMoveToLocation(m_SelectedUnits[i]->GetController(), MoveLocation);
		DrawDebugSphere(GetWorld(), MoveLocation, 25, 10, FColor::Red, false, 3.f);
	}
}