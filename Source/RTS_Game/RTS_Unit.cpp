// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS_Unit.h"
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
		
	// All stats defaulted to 0 or NONE
	m_Stats = new FRTS_UnitStats;
}

ARTS_Unit::~ARTS_Unit()
{
	delete m_Stats;
}

// Called when the game starts or when spawned
void ARTS_Unit::BeginPlay()
{
	Super::BeginPlay();
	m_SelectionIndicator->SetVisibility(false);

}

void ARTS_Unit::Move(FVector &a_Location)
{
	// Simple fill-in version for testing THIS SHOULD ALWAYS BE OVERRIDEN
	UNavigationSystem::SimpleMoveToLocation(this->GetController(), a_Location);
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
