// Christopher Laganella - Ramapo College of New Jersey senior project

#include "RTS_CapturePoint.h"
#include "RTS_Unit.h"
#include "DrawDebugHelpers.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"

/**
* Binds functions BeginOverlap and EndOverlap to this actor. Sets default values
*/
ARTS_CapturePoint::ARTS_CapturePoint()
{
	PrimaryActorTick.bCanEverTick = true;

	OnActorBeginOverlap.AddDynamic(this, &ARTS_CapturePoint::BeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &ARTS_CapturePoint::EndOverlap);
	m_CurrentScore = 0;
	m_MaxScore = 100;
}

/**
* Called when spawned. Tells the engine to start a recurring timer every 1 second 10 seconds from now. Draws this as box
*/
void ARTS_CapturePoint::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(m_AttackLockoutTimer, this, &ARTS_CapturePoint::OnTimerTick, 1.f, true, 10.f);
	DrawDebugBox(GetWorld(), GetActorLocation(), GetComponentsBoundingBox().GetExtent(), FColor::Purple, true, -1, 0, 5);
}

/**
* Called when this another actor overlaps this actor. Checks if the unit is not on this team and then adds it to m_Overlapping actors if true
* @param a_Trigger AActor * - The actor that called this function (this)
* @param a_OtherActor AActor * - The actor that triggered this function to be called
*/
void ARTS_CapturePoint::BeginOverlap(AActor *a_Trigger, AActor * a_OtherActor)
{
	ARTS_Unit *unitCast = Cast<ARTS_Unit>(a_OtherActor);
	if (unitCast)
	{
		if (unitCast->GetTeamColor() != m_TeamColor)
		{
			m_OverlappingAttackers.Add(unitCast);
		}
	}
}

/**
* Called when an actor that was overlapping this leaves. Removes the unit from m_OverlappingAttackers
* @param a_Trigger AActor * - The actor that called this function (this)
* @param a_OtherActor AActor * - The actor that triggered this function to be called
*/
void ARTS_CapturePoint::EndOverlap(AActor *a_Trigger, AActor *a_OtherActor)
{
	ARTS_Unit *unitCast = Cast<ARTS_Unit>(a_OtherActor);
	if (unitCast)
	{
		m_OverlappingAttackers.Remove(unitCast);
	}
}

/**
* Called once every second adds 1 to the score if there is an actor overlapping
*/
void ARTS_CapturePoint::OnTimerTick()
{
	if (m_OverlappingAttackers.Num())
	{
		m_CurrentScore++;
		if (m_CurrentScore >= m_MaxScore)
		{
			 AttackersWin();
		}
	}

	// For debugging purposes
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Current score: %d / %d"), m_CurrentScore, m_MaxScore), 1);
	}
}

/**
* If the score reaches max broadcast this event
*/
void ARTS_CapturePoint::AttackersWin()
{
	m_AttackerCapturedPoint.Broadcast();
}
