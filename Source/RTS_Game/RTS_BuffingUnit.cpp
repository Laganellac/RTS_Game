// Christopher Laganella - Ramapo College of New Jersey senior project

#include "RTS_BuffingUnit.h"

#include "Runtime/Engine/Classes/Components/SphereComponent.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"


ARTS_BuffingUnit::ARTS_BuffingUnit()
{
	// Setup attack trigger around unit
	m_BuffTrigger = CreateDefaultSubobject<USphereComponent>("BuffTrigger");
	m_BuffTrigger->SetupAttachment(RootComponent);
	m_BuffTrigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	m_BuffTrigger->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel2);		
	m_BuffTrigger->OnComponentBeginOverlap.AddDynamic(this, &ARTS_BuffingUnit::OnOverlap);
	m_BuffTrigger->OnComponentEndOverlap.AddDynamic(this, &ARTS_BuffingUnit::OnEndOverlap);


	m_Stats.Range = 500.f;

	// Default value for m_TargetColor
	m_TargetColor = ETeamColor::RED;
}

void ARTS_BuffingUnit::BeginPlay()
{
	Super::BeginPlay();

	m_BuffTrigger->SetSphereRadius(m_Stats.Range, true);
}

void ARTS_BuffingUnit::Buff(ARTS_Unit *a_TargetUnit)
{
	// For debugging purposes
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString(TEXT("Buffing ") + a_TargetUnit->GetName()));
	}

}

void ARTS_BuffingUnit::UnBuff(ARTS_Unit * a_TargetUnit)
{
	// For debugging purposes
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString(TEXT("No longer buffing ") + a_TargetUnit->GetName()));
	}
}

void ARTS_BuffingUnit::OnOverlap(UPrimitiveComponent *a_ThisComp, AActor *a_OtherActor, UPrimitiveComponent *a_OtherComp, int32 a_OtherBodyIndex, bool a_bFromSweep, const FHitResult &a_SweepResult)
{
	ARTS_Unit *unitCast;

	unitCast = Cast<ARTS_Unit>(a_OtherActor);
	if (unitCast)
	{
		// Add the unit to targeted units if it is on the right team or if this unit buffs all team's units
		if (unitCast->GetTeamColor() == m_TargetColor || m_TargetColor == ETeamColor::ALL)
		{
			m_TargetedUnits.Add(unitCast);
			Buff(unitCast);
		}
	}
}

void ARTS_BuffingUnit::OnEndOverlap(UPrimitiveComponent *a_ThisComp, AActor *a_OtherActor, UPrimitiveComponent *a_OtherComp, int32 a_OtherBodyIndex)
{
	ARTS_Unit *unitCast;

	unitCast = Cast<ARTS_Unit>(a_OtherActor);
	if (unitCast)
	{
		m_TargetedUnits.Remove(unitCast);
		UnBuff(unitCast);
	}
}
