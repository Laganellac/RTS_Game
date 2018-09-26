// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "RTS_Lib.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RTS_Unit.generated.h"

enum class EAttackResult
{
	NONE,
	ALIVE,
	DEAD,
};

UCLASS()
class RTS_GAME_API ARTS_Unit : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARTS_Unit();

	FORCEINLINE bool IsDead() { return (m_Stats.CurrentHealth <= 0.f); };

	virtual void MoveTo(const FVector &a_Location);

	EAttackResult RecieveDamage(class ARTS_Unit *a_Source, const float &a_Damage);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void SetTeamColor(ETeamColor a_TeamColor);

	void SetSelected();

	void SetDeselected();

	FRTS_UnitStats *GetUnitStatsForBuff(class ARTS_BuffingUnit *a_BuffingUnit);

	FORCEINLINE const FRTS_UnitStats GetUnitStats() const { return m_Stats; };

	// Accessor functions that are exposed to blueprints (20 min 9.1.18)
	UFUNCTION(BlueprintPure, Category = "Combat")
	FORCEINLINE float GetAttackSpeed() { return m_Stats.AttackSpeed; };

	UFUNCTION(BlueprintPure, Category = "Combat")
	FORCEINLINE float GetDamage() { return m_Stats.Damage; };

	UFUNCTION(BlueprintPure, Category = "Combat")
	FORCEINLINE float GetRange() { return m_Stats.Range; };

	UFUNCTION(BlueprintPure, Category = "Energy")
	FORCEINLINE float GetCurrentEnergy() { return m_Stats.CurrentEnergy; };

	UFUNCTION(BlueprintPure, Category = "Energy")
	FORCEINLINE float GetTotalEnergy() { return m_Stats.TotalEnergy; };

	UFUNCTION(BlueprintPure, Category = "Health")
	FORCEINLINE float GetCurrentHealth() { return m_Stats.CurrentHealth; };

	UFUNCTION(BlueprintPure, Category = "Health")
	FORCEINLINE float GetTotalHealth() { return m_Stats.TotalHealth; };

	UFUNCTION(BlueprintPure, Category = "Mobility")
	FORCEINLINE float GetSpeed() { return m_Stats.Speed; };

	UFUNCTION(BlueprintPure, Category = "TeamColor")
	FORCEINLINE ETeamColor GetTeamColor() { return m_Stats.TeamColor; };

	UFUNCTION(BlueprintPure)
	FORCEINLINE EUnitName GetUnitName() { return m_Stats.UnitName; };

	UFUNCTION(BlueprintPure)
	FORCEINLINE FString GetUnitNameAsString() { return m_Stats.UnitNameString; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Die();

	UFUNCTION()
	virtual void Move();

	UFUNCTION()
	virtual void StopMoving();

	// Unit properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRTS_UnitStats m_Stats;

	// Lets the player know this unit is selected
	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* m_SelectionIndicator;

	FVector m_MoveLocation;

private:
	
	UPROPERTY(EditDefaultsOnly)
	class USpotLightComponent *m_ColorLight;
	

};
