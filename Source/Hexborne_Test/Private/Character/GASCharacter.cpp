// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GASCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/GASAbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/GASPlayerController.h"
#include "Player/GASPlayerState.h"
#include "UI/HUD/GASHUD.h"

AGASCharacter::AGASCharacter()
{
	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetMesh(), TEXT("rootSocket"));
	CameraBoom->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));
	CameraBoom->TargetArmLength = 1000.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0, 400.f, 0);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
}

void AGASCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Init ability actor info for the Server
	InitAbilityActorInfo();
	AddCharacterAbilities();
}

void AGASCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Init ability actor info for the Server
	InitAbilityActorInfo(); 
}

int32 AGASCharacter::GetPlayerLevel()
{
	AGASPlayerState* GASPlayerState = GetPlayerState<AGASPlayerState>();
	check(GASPlayerState);
	return GASPlayerState->GetPlayerLevel();
}

void AGASCharacter::InitAbilityActorInfo()
{
	AGASPlayerState* GASPlayerState = GetPlayerState<AGASPlayerState>();
	check(GASPlayerState);
	GASPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(GASPlayerState, this);
	Cast<UGASAbilitySystemComponent>(GASPlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();
	AbilitySystemComponent = GASPlayerState->GetAbilitySystemComponent();
	AttributeSet = GASPlayerState->GetAttributeSet();

	if (AGASPlayerController* GASPlayerController = Cast<AGASPlayerController>(GetController()))
	{
		if(AGASHUD* GASHUD = Cast<AGASHUD>(GASPlayerController->GetHUD()))
		{
			GASHUD->InitOverlay(GASPlayerController, GASPlayerState, AbilitySystemComponent, AttributeSet);
			
		}
		
	}
	InitializeDefaultAttributes();
}
