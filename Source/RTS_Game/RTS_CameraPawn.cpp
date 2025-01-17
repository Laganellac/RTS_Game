// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS_CameraPawn.h"
#include "RTS_PlayerController.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/StaticMesh.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"


/**
* Sets up all components to their proper lengths and sets default values
*/
ARTS_CameraPawn::ARTS_CameraPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Component that handles the pawn's movement
	CreateDefaultSubobject<UFloatingPawnMovement>("PawnMovement");

	// Create the object's components
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");

	// Create the sphere that will represent where the pawn is
	m_Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	m_Mesh->SetupAttachment(RootComponent);
	ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Game/StarterContent/Props/MaterialSphere.MaterialSphere'"));
	m_Mesh->SetStaticMesh(MeshAsset.Object);
	m_Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Create the spring arm and attach it to the root (this will hold the camera away from the root on an angle)
	m_SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArms");
	m_SpringArm->SetupAttachment(RootComponent);
	m_SpringArm->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	m_SpringArm->TargetArmLength = 1500.f;
	m_SpringArm->bDoCollisionTest = false;

	// Create the camera and attach it to the springarm
	m_Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	m_Camera->SetupAttachment(m_SpringArm);

	// Dont allow movement until told to
	m_CanMove = false;
}

/**
* Called every frame. Checks if the camera is allowed to move then GetCameraPanDirection() if true
* @param DeltaTime float - Constant defined by the engine every tick
*/
void ARTS_CameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// If we've been told to move
	if (m_CanMove)
	{
		GetCameraPanDirection();
	}
}

/**
* Binds MoveForward() and MoveRight() to keys. Not currently used but was once used to testing and could be used again
* @param PlayerInputComponent UInputCompoennt * - A reference to the player inputcomponent that handle keybindings to actions
*/
void ARTS_CameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ARTS_CameraPawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ARTS_CameraPawn::MoveRight);
}

/**
* Moves the camerapawn forward or backward depending on a_AxisValue
* @param a_AxisValue float - Between -1.f and 1.f negative means move backward
*/
void ARTS_CameraPawn::MoveForward(float a_AxisValue)
{
	AddMovementInput(GetActorForwardVector(), a_AxisValue);
}

/**
* Moves the camerapawn left or right depending on a_AxisValue
* @param a_AxisValue - Between -1.f and 1.f negative means move left
*/
void ARTS_CameraPawn::MoveRight(float a_AxisValue)
{
	AddMovementInput(GetActorRightVector(), a_AxisValue);
}

/**
* Called when spawned. Makes the ball invisible to the player and gets m_PlayerController
*/
void ARTS_CameraPawn::BeginPlay()
{
	Super::BeginPlay();

	// Makes the ball invisible when in-game
	m_Mesh->SetVisibility(false);

	m_PlayerController = Cast<ARTS_PlayerController>(GetController());
	if (m_PlayerController != NULL)
	{
		
	}
}

/**
* Gets the mouse location from m_PlayerController and then calls the respective move function based on the location. Outputs mouselocation to dev console.
*/
void ARTS_CameraPawn::GetCameraPanDirection()
{
	// Just incase theres no player controller
	if (m_PlayerController == NULL)
	{
		return;
	}

	float mousePositionX;
	float mousePositionY;
	int32 screenSizeX;
	int32 screenSizeY;


	m_PlayerController->GetMousePosition(mousePositionX, mousePositionY);
	m_PlayerController->GetViewportSize(screenSizeX, screenSizeY);
	m_PlayerController->ClientMessage(FString::Printf(TEXT("cX: %f, cY: %f    mX: %d, mY: %d"), mousePositionX, mousePositionY, screenSizeX, screenSizeY));

	// If mouseX value is invalid ignore it
	if (mousePositionX < 0 || mousePositionX > screenSizeX)
	{
		// Do nothing
	}

	// If the mouse hits the left side of the screen
	else if (mousePositionX <= MOVEMENT_MARGIN)
	{
		MoveRight(-1.f);
	}

	// If the mouse hits the right of the screen
	else if (mousePositionX >= screenSizeX - MOVEMENT_MARGIN)
	{
		MoveRight(1.f);
	}

	///////////////////////////////////////////

	// If the mouseY value is invalid ignore it
	if (mousePositionY < 0 || mousePositionY > screenSizeY)
	{
		// Do nothing
	}

	// If the mouse hits the top of the screen
	else if (mousePositionY <= MOVEMENT_MARGIN)
	{
		MoveForward(1.f);
	}

	// If the mouse hits the bottom of the screen
	else if (mousePositionY >= screenSizeY - MOVEMENT_MARGIN)
	{
		MoveForward(-1.f);
	}
}
