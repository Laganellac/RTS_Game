// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "RTS_Lib.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RTS_Unit.generated.h"

UCLASS()
class RTS_GAME_API ARTS_Unit : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARTS_Unit();

	~ARTS_Unit();

	virtual void MoveTo(FVector &a_Location);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetSelected();

	void SetDeselected();

	// Accessor functions that are exposed to blueprints (20 min 9.1.18)
	UFUNCTION(BlueprintPure, Category = "Combat")
	FORCEINLINE float GetDamage() { return m_Stats->Damage; };

	UFUNCTION(BlueprintPure, Category = "Combat")
	FORCEINLINE float GetRange() { return m_Stats->Range; };

	UFUNCTION(BlueprintPure, Category = "Energy")
	FORCEINLINE float GetCurrentEnergy() { return m_Stats->CurrentEnergy; };

	UFUNCTION(BlueprintPure, Category = "Energy")
	FORCEINLINE float GetTotalEnergy() { return m_Stats->TotalEnergy; };

	UFUNCTION(BlueprintPure, Category = "Health")
	FORCEINLINE float GetCurrentHealth() { return m_Stats->CurrentHealth; };

	UFUNCTION(BlueprintPure, Category = "Health")
	FORCEINLINE float GetTotalHealth() { return m_Stats->TotalHealth; };

	UFUNCTION(BlueprintPure, Category = "Mobility")
	FORCEINLINE float GetSpeed() { return m_Stats->Speed; };

	UFUNCTION(BlueprintPure, Category = "TeamColor")
	FORCEINLINE enum ETeamColor GetTeamColor() { return m_Stats->TeamColor; };

protected:

	void Move(FVector &a_Location);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	FRTS_UnitStats *m_Stats;

	// Lets the player know this unit is selected
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* m_SelectionIndicator;

private:
	

	

};
