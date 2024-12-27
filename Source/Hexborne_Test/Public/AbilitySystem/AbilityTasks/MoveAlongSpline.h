#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "Components/SplineComponent.h"
#include "MoveAlongSpline.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMoveTaskCompletedSignature, bool, MoveFinished);

/**
 * Gameplay Task to move an actor along a spline
 */
UCLASS()
class HEXBORNE_TEST_API UGameplayTask_MoveAlongSpline : public UAbilityTask
{
    GENERATED_BODY()

public:
    
    UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (DisplayName = "MoveAlongSpline",HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "true"))
    static UGameplayTask_MoveAlongSpline* CreateMoveAlongSplineTask(
        UGameplayAbility* OwningAbility,
        USkeletalMeshComponent* MeshComp,
        USplineComponent* SplineComp,
        float Duration
    );

    UPROPERTY(BlueprintAssignable)
    FMoveTaskCompletedSignature OnMoveFinished;


protected:
    UPROPERTY()
    USplineComponent* TargetSpline;
    
    UPROPERTY()
    float SplineDuration;

    UPROPERTY()
    USkeletalMeshComponent* MeshComp;
    
    float ElapsedTime;
    
    void UpdateTask(float DeltaTime);
    
    void FinishTask();

private:
    virtual void Activate() override;
    
    FTimerHandle TimerHandle;
};
