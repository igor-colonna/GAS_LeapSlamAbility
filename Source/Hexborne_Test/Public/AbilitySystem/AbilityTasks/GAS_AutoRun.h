// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "GAS_AutoRun.generated.h"

class USplineComponent;
class UNavigationPath;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAutoRunCompleted);

/**
 * 
 */
UCLASS()
class HEXBORNE_TEST_API UGAS_AutoRun : public UAbilityTask
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UGAS_AutoRun* CreateAutoRunTask(
		UGameplayAbility* OwningAbility,
		const FVector& Destination, 
		USplineComponent* Spline,
		UNavigationPath* Path,
		float AcceptanceRadius = 50.f,
		bool bDebugLines = false);
	
	UPROPERTY(BlueprintAssignable)
	FOnAutoRunCompleted OnCompleted;

protected:
	UGAS_AutoRun(const FObjectInitializer& ObjectInitializer);
	
	virtual void TickTask(float DeltaTime) override;
	
	virtual void Activate() override;
	
	FVector CachedDestination;
	
	UPROPERTY()
	TObjectPtr<USplineComponent> Spline;

	UPROPERTY(EditAnywhere)
	bool bDebugLines = false;
	
	float AutoRunAcceptanceRadius;
	
	bool bIsCompleted;

	UNavigationPath* Path;

private:

	void DebugLines();
};

