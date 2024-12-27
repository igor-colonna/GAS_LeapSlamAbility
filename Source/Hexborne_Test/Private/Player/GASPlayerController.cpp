// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/GASPlayerController.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "GASGameplayTags.h"
#include "AbilitySystem/GASAbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "Character/GASCharacter.h"
#include "Components/SplineComponent.h"
#include "Input/GASInputComponent.h"
#include "Interaction/EnemyInterface.h"

AGASPlayerController::AGASPlayerController()
{
	bReplicates = true;

	Spline = CreateDefaultSubobject<USplineComponent>("Spline");
}

void AGASPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}

void AGASPlayerController::CursorTrace()
{
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;

	LastActor = ThisActor;
	ThisActor = CursorHit.GetActor();

	if(ThisActor != LastActor)
	{
		if (LastActor) LastActor->UnHighlightActor();
		if (ThisActor) ThisActor->HighlightActor();
	}
}

FHitResult AGASPlayerController::GetCursorHit() const
{
	return CursorHit;
}

void AGASPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{

	if (GetASC())
	{
		GetASC()->AbilityInputTagHeld(InputTag);
	}
	GEngine->AddOnScreenDebugMessage(1, 3, FColor::Red, *InputTag.ToString());
}

void AGASPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (GetASC())
	{
		GetASC()->AbilityInputTagHeld(InputTag);
	}

}

void AGASPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	
	if (!InputTag.MatchesTagExact(FGASGameplayTags::Get().InputTag_LMB))
	{
		if (GetASC())
		{
			GetASC()->AbilityInputTagHeld(InputTag);
		}
		return;
	}
	
}

UGASAbilitySystemComponent* AGASPlayerController::GetASC()
{
	if(GASAbilitySystemComponent == nullptr)
	{
		GASAbilitySystemComponent = Cast<UGASAbilitySystemComponent>(
			UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	return GASAbilitySystemComponent;
	
}


void AGASPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(GASContext);
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if(Subsystem)
	{
		Subsystem->AddMappingContext(GASContext, 0);
	}

	if (APawn* MainPawn = GetPawn())
	{
		if (AGASCharacter* MainCharacter = Cast<AGASCharacter>(MainPawn))
		{
			FollowCamera = MainCharacter->GetFollowCamera();
		}
	}
	
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);

}

void AGASPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UGASInputComponent* GASInputComponent = CastChecked<UGASInputComponent>(InputComponent);

	GASInputComponent->BindAbilityActions(InputConfig, this,
		&ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);

	GASInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AGASPlayerController::Move);
}		

void AGASPlayerController::Move(const FInputActionValue& InputActionValue)
{

	InputAxisVector = InputActionValue.Get<FVector2d>();
	const FRotator Rotation = FollowCamera->GetComponentRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.0f);
	
	ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
}