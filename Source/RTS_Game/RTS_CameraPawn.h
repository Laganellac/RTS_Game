// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "RTS_CameraPawn.generated.h"

UCLASS()
class RTS_GAME_API ARTS_CameraPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ARTS_CameraPawn();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// a_Val either -1.0 or 1.0 depending on keypress
	void MoveForward(float AxisValue);

	// a_Val either -1.0 or 1.0 depending on keypress
	void MoveRight(float AxisValue);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UFUNCTION()
	void GetCameraPanDirection();

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* m_Mesh;

	UPROPERTY(EditAnywhere)
	class UCameraComponent* m_Camera;

	UPROPERTY(EditAnywhere)
	class USpringArmComponent* m_SpringArm;

	UPROPERTY()
	class ARTS_PlayerController* m_PlayerController;

	UPROPERTY()
	float MOVEMENT_MARGIN = 15.f;

};
