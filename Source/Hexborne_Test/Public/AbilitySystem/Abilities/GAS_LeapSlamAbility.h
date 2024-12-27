// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/GASGameplayAbility.h"
#include "GAS_LeapSlamAbility.generated.h"

/**
 * 
 */


class AGASCharacter;
class USplineComponent;

UENUM(BlueprintType)
enum class ECalculatePointResult : uint8
{
	Invalid UMETA(DisplayName="Invalid Path"),
	Valid   UMETA(DisplayName="Valid Path")
};

UCLASS()
class HEXBORNE_TEST_API UGAS_LeapSlamAbility : public UGASGameplayAbility
{
	GENERATED_BODY()

public:

	// UPROPERTY(BlueprintAssignable, Category = "Leap Slam")
	// FSuccessDelegate OnSuccess;
	//
	// UPROPERTY(BlueprintAssignable, Category = "Leap Slam")
	// FSuccessDelegate OnFailure;
	

	UGAS_LeapSlamAbility();
	UPROPERTY(BlueprintReadOnly)
	AGASCharacter* GASCharacter;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USplineComponent* SplineComp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float AbilityRange = 500.f; 

private:
	UFUNCTION(BlueprintCallable, Category="SplineArc")
	void CreateArc(const FVector& StartPoint, const FVector& EndPoint, float ArcHeight, FVector& OutEnd);

	UFUNCTION(BlueprintCallable, Category = "Leap Slam|Utility")
	FVector CalculatePointWithinRange(
		const FVector& StartLocation,
		const FVector& TargetLocation,
		ECalculatePointResult& Branches,
		FVector& OutLocation,
		UNavigationPath*& OutPath
		);


	void DebugLines();

	
protected:
	
	virtual void ActivateAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData
	) override;

	virtual void EndAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		bool bReplicateEndAbility,
		bool bWasCancelled
	) override;

	UPROPERTY(EditAnywhere);
	bool bDebugLines = false;
	
};



