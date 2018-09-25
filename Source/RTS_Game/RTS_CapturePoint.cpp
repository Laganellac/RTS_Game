// Christopher Laganella - Ramapo College of New Jersey senior project

#include "RTS_CapturePoint.h"
#include "RTS_Unit.h"
#include "DrawDebugHelpers.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"


ARTS_CapturePoint::ARTS_CapturePoint()
{
	PrimaryActorTick.bCanEverTick = true;

	OnActorBeginOverlap.AddDynamic(this, &ARTS_CapturePoint::BeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &ARTS_CapturePoint::EndOverlap);
	m_CurrentScore = 0;
	m_MaxScore = 100;
}

void ARTS_CapturePoint::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(m_AttackLockoutTimer, this, &ARTS_CapturePoint::OnTimerTick, 1.f, true, 10.f);
	DrawDebugBox(GetWorld(), GetActorLocation(), GetComponentsBoundingBox().GetExtent(), FColor::Purple, true, -1, 0, 5);
}

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

void ARTS_CapturePoint::EndOverlap(AActor *a_Trigger, AActor *a_OtherActor)
{
	ARTS_Unit *unitCast = Cast<ARTS_Unit>(a_OtherActor);
	if (unitCast)
	{
		m_OverlappingAttackers.Remove(unitCast);
	}
}

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

void ARTS_CapturePoint::AttackersWin()
{
	m_AttackerCapturedPoint.Broadcast();
}
