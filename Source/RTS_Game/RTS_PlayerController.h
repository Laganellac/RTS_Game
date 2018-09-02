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

	~ARTS_PlayerController();

	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	virtual void Tick(float a_DeltaTime) override;

	class ARTS_HUD* m_CurrentHUD;

protected:

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

private:
	FRTS_PlayerStats *m_Stats;
	
	// Used to check if the player is attempting to group two units together
	bool m_GroupingUnits;

	FHitResult m_InitialSelectionClick;

	// Stores the group of currently selected units
	TArray<class ARTS_Unit *> m_SelectedUnits;
};
