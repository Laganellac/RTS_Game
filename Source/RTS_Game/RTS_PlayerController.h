// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "RTS_Lib.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RTS_PlayerController.generated.h"


/**
 * 
 */
UCLASS()
class RTS_GAME_API ARTS_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ARTS_PlayerController();

	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	virtual void Tick(float a_DeltaTime) override;

	void AddUnit(EUnitName a_UnitName);

	void StartRound();

	class ARTS_Unit *GetSelectedUnit();

	FORCEINLINE int32 GetCurrentGold() { return m_Stats.CurrentGold; };

	EUnitName GetNextUnitToSpawn();

	FORCEINLINE ETeamColor GetTeamColor() { return m_Stats.TeamColor; };

	FORCEINLINE void SetTeamColor(ETeamColor a_TeamColor) { m_Stats.TeamColor = a_TeamColor; };

	class ARTS_HUD* m_CurrentHUD;

protected:

	void Attack(FHitResult &a_Hit);

	UFUNCTION()
	void AttackPressed();

	// Deselects each unit in the array and then empties it
	void DeselectUnits();

	// Checks if the given unit is on the same team as the player
	bool IsOnPlayerTeam(class ARTS_Unit *a_Unit);

	UFUNCTION()
	void GroupUnitsPressed();

	UFUNCTION()
	void GroupUnitsReleased();

	UFUNCTION()
	void MovePressed();

	UFUNCTION()
	void SelectionPressed();

	void SpawnUnit(FHitResult &a_Hit);

private:
	UFUNCTION()
	void OnPointCapture();

	UPROPERTY(VisibleAnywhere)
	FRTS_PlayerStats m_Stats;	

	// Used to check if the player is attempting to attack
	bool m_Attacking;

	// Used to check if the player is attempting to group two units together
	bool m_GroupingUnits;

	// Used to check if this player has spawned a capture point yet
	bool m_MustSpawnPoint;

	// Used to check if this is the start of the round where units are being spawned
	bool m_PlacingUnits;

	FHitResult m_InitialSelectionClick;

	// Stores the group of currently selected units
	UPROPERTY()
	TArray<class ARTS_Unit *> m_SelectedUnits;

	UPROPERTY()
	class URTS_BlueprintRefs *m_BlueprintRefs;

	UPROPERTY()
	TArray<EUnitName> m_PurchasedUnits;
};
