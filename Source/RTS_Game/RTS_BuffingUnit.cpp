// Christopher Laganella - Ramapo College of New Jersey senior project

#include "RTS_BuffingUnit.h"

#include "Runtime/Engine/Classes/Components/SphereComponent.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"

/**
* Creates the m_BuffTrigger component used for generating overlap events
*/
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

/**
* Called when this is spawned into the world, sets m_BuffTrigger's radius to the units range
*/
void ARTS_BuffingUnit::BeginPlay()
{
	Super::BeginPlay();

	m_BuffTrigger->SetSphereRadius(m_Stats.Range, true);
}

/**
* A base version that just outputs to the screen. To be overridden
* @param a_TargetUnit ARTS_Unit * - The the unit that has entered the buff range 
*/
void ARTS_BuffingUnit::Buff(ARTS_Unit *a_TargetUnit)
{
	// For debugging purposes
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString(TEXT("Buffing ") + a_TargetUnit->GetName()));
	}

}

/**
* A base version that just outputs to the screen. To be overridden
* @param a_TargetUnit ARTS_Unit * -The unit that has left the buff range
*/
void ARTS_BuffingUnit::UnBuff(ARTS_Unit * a_TargetUnit)
{
	// For debugging purposes
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString(TEXT("No longer buffing ") + a_TargetUnit->GetName()));
	}
}

/**
* The function that will be called whenever an actor enters m_BuffTrigger. Checks unit is on correct team then passes it into Buff
* @param a_ThisComp UPrimitiveCOmponent * - The component that called this function
* @param a_OtherActor AActor * - The actor that entered the range (The one that triggered this call)
* @param a_OtherComp UPrimitiveComponent * - The specific component on a_OtherActor that triggered this call
* @param a_OtherBodyIndex in32 - Required by engine but unused here
* @param a_bFromSweep bool - Required by engine but unused here
* @param a_SweepResult const FHitResult & - Required by engine but unused here
*/
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

/**
* The function that will be called whenever an actor exits m_BuffTrigger. Check if the unit is currently being buffed then passes it to UnBuff if true
* @param a_ThisComp UPrimitiveCOmponent * - The component that called this function
* @param a_OtherActor AActor * - The actor that entered the range (The one that triggered this call)
* @param a_OtherComp UPrimitiveComponent * - The specific component on a_OtherActor that triggered this call
* @param a_OtherBodyIndex in32 - Required by engine but unused here
* @param a_bFromSweep bool - Required by engine but unused here
* @param a_SweepResult const FHitResult & - Required by engine but unused here
*/
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