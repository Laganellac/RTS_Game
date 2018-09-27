// Christopher Laganella - Ramapo College of New Jersey senior project

#pragma once

#include "RTS_Lib.h"
#include "CoreMinimal.h"
#include "Engine/TriggerCapsule.h"
#include "RTS_CapturePoint.generated.h"



/** 
 * Class for handling the logic of the capture point
 * @author Christopher Laganella
 */
UCLASS()
class RTS_GAME_API ARTS_CapturePoint : public ATriggerCapsule
{
	GENERATED_BODY()
	
public:

	ARTS_CapturePoint();

	DECLARE_EVENT(ARTS_CapturePoint, FAttackerCapturedPoint)
	FAttackerCapturedPoint &OnChanged() { return m_AttackerCapturedPoint; };

	void SetTeamColor(ETeamColor a_TeamColor) { m_TeamColor = a_TeamColor; };

protected:

	virtual void BeginPlay() override;
	
	UFUNCTION()
	void BeginOverlap(AActor *a_OverlappingActor, AActor *a_OtherActor);

	UFUNCTION()
	void EndOverlap(AActor *a_OverlappingActor, AActor *a_OtherActor);

	UFUNCTION()
	void OnTimerTick();

private:

	UFUNCTION()
	void AttackersWin();

	FAttackerCapturedPoint m_AttackerCapturedPoint;

	ETeamColor m_TeamColor;

	uint8 m_CurrentScore;
	uint8 m_MaxScore;

	// 
	FTimerHandle m_AttackLockoutTimer;

	TArray<class ARTS_Unit*> m_OverlappingAttackers;
};
