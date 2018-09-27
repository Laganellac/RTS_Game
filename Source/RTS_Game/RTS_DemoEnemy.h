// Christopher Laganella - Ramapo College of New Jersey senior project

#pragma once

#include "RTS_Lib.h"
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RTS_DemoEnemy.generated.h"

/** A class to hold info about the opponent
 * @author Christopher Laganella
 */
UCLASS()
class RTS_GAME_API URTS_DemoEnemy : public UObject
{
	GENERATED_BODY()
	
public:
	URTS_DemoEnemy();

	void ArmyAttack();

	void Construct(class ARTS_PlayerController *a_OwningController, class ARTS_CapturePoint *a_CapturePoint, const FVector &a_EnemySpawnLoc);

	void SpawnArmy();

	int GetNumAlive();
	
private:

	void InitializeArmyList();

	ETeamColor m_TeamColor;

	FVector m_SpawnLocationBase;

	FVector m_EnemyCapturePointLoc;

	UPROPERTY()
	class URTS_BlueprintRefs *m_BlueprintRefs;

	class ARTS_PlayerController *m_OwningController;
	
	UPROPERTY()
	TArray<EUnitName> m_ArmyList;

	UPROPERTY()
	TArray<class ARTS_Unit *> m_Units;
};
