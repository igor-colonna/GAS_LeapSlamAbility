// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"
#include "GASPlayerController.generated.h"

class UCameraComponent;
class UGASAbilitySystemComponent;
struct FGameplayTag;
class UInputMappingContext;
class UInputAction;
class UGASInputConfig;
class USplineComponent;

struct FInputActionValue;

class IEnemyInterface;

/**
 * 
 */
UCLASS()
class HEXBORNE_TEST_API AGASPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AGASPlayerController();
	virtual void PlayerTick(float DeltaTime) override;

	FHitResult GetCursorHit() const;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector ForwardDirection;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector RightDirection;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector2D InputAxisVector;

	UPROPERTY(BlueprintReadWrite, Category = "Movement")
	bool bCanMove = true;
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	
	UPROPERTY()
	UCameraComponent* FollowCamera;
	
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> GASContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	void Move(const FInputActionValue& InputActionValue);

	void CursorTrace();

	TScriptInterface<IEnemyInterface> LastActor;
	TScriptInterface<IEnemyInterface> ThisActor;
	FHitResult CursorHit;
	
	void AbilityInputTagPressed(FGameplayTag Tag);
	void AbilityInputTagReleased(FGameplayTag Tag);
	void AbilityInputTagHeld(FGameplayTag Tag);
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UGASInputConfig> InputConfig;

	UPROPERTY()
	TObjectPtr<UGASAbilitySystemComponent> GASAbilitySystemComponent;

	UGASAbilitySystemComponent* GetASC();

	FVector CachedDestination = FVector::ZeroVector;
	float FollowTime = 0.f;
	float ShortPressThreshold = 0.5f;
	bool bAutoRunning = false;
	bool bTargeting = false;

	UPROPERTY(EditDefaultsOnly)
	float AutoRunAcceptanceRadius = 50.f;

	TObjectPtr<USplineComponent> Spline;

	void AutoRun();

	
	
};
