// Christopher Laganella - Ramapo College of New Jersey senior project

#pragma once

#include "RTS_Lib.h"
#include "CoreMinimal.h"
#include "RTS_Unit.h"
#include "RTS_AttackingUnit.generated.h"

/**
 * 
 */
UCLASS()
class RTS_GAME_API ARTS_AttackingUnit : public ARTS_Unit
{
	GENERATED_BODY()

public:
	ARTS_AttackingUnit();

	// Used when the ground is attack clicked
	void AttackMove(const FVector &a_Location);

	// Used when a unit is attack clicked as opposed to the ground
	void AttackTargetUnit(ARTS_Unit *a_TargetUnit);

	// Needs to be overriden to reset attacking flags because this will be called by controller
	virtual void MoveTo(const FVector &a_Location) override;

	FORCEINLINE bool IsAttackingMoving() { return m_IsAttackMoving; };

protected:

	UFUNCTION()
	// Attack using the information stored in m_TargetUnits
	virtual void Attack();
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	virtual void TickAttackMove();

	UFUNCTION()
	virtual void TickAttackTarget();

	// A sphere around the unit looking for overlaps with other units
	UPROPERTY(EditDefaultsOnly)
	class USphereComponent* m_AttackTrigger;

	// A boolean that determines if this unit will attack any enemy in range
	bool m_IsAttackMoving;

	// A boolean that determines if this unit is specifically targetting 1 unit
	bool m_IsAttackingTarget;

	// The unit that is currently being targeted
	class ARTS_Unit *m_TargetUnit;

	enum ETeamColor m_TargetTeamColor;
	
	// List of units that this unit will target with an attack
	TArray<ARTS_Unit *> m_TargetedUnits;

	FTimerHandle m_AttackLockoutTimer;

private:
	// List of actors that overlap m_AttackTrigger
	TArray<AActor *> m_OverlappingActors;
};
