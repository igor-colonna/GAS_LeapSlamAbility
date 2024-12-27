// Copyright Igorcolonna

#include "AbilitySystem/AbilityTasks/MoveAlongSpline.h"

#include <ThirdParty/ShaderConductor/ShaderConductor/External/DirectXShaderCompiler/include/dxc/DXIL/DxilConstants.h>

#include "TimerManager.h"
#include "GameFramework/Actor.h"

UGameplayTask_MoveAlongSpline* UGameplayTask_MoveAlongSpline::CreateMoveAlongSplineTask(
    UGameplayAbility* OwningAbility,
    USkeletalMeshComponent* MeshComp,
    USplineComponent* SplineComp,
    float Duration)
{
    UGameplayTask_MoveAlongSpline* MyTask = NewAbilityTask<UGameplayTask_MoveAlongSpline>(OwningAbility);
    MyTask->TargetSpline = SplineComp;
    MyTask->MeshComp = MeshComp;
    MyTask->SplineDuration = Duration;
    return MyTask;
}

void UGameplayTask_MoveAlongSpline::Activate()
{
    Super::Activate();

    if (!TargetSpline || !GetOwnerActor())
    {
        EndTask();
        return;
    }
    
    ElapsedTime = 0.f;

    FTimerDelegate TimerDelegate;
    TimerDelegate.BindUObject(this, &UGameplayTask_MoveAlongSpline::UpdateTask, GetWorld()->GetDeltaSeconds());

    
    GetWorld()->GetTimerManager().SetTimer(
        TimerHandle,
        TimerDelegate,
        0.01f, 
        true   
    );
}

void UGameplayTask_MoveAlongSpline::UpdateTask(float DeltaTime)
{
    if (!TargetSpline || !GetOwnerActor())
    {
        FinishTask();
        return;
    }

    ElapsedTime += 0.01f;   

    float Alpha = ElapsedTime / SplineDuration;
    if (Alpha >= 1.f)
    {
        
        FinishTask();
        return;
    }
    
    float Distance = Alpha * TargetSpline->GetSplineLength();
    FVector NewLocation = TargetSpline->GetLocationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);
    //FRotator NewRotation = TargetSpline->GetRotationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);
    if (MeshComp)
    {
        //MeshComp->SetWorldLocationAndRotation(NewLocation, NewRotation);
        
        MeshComp->SetWorldLocation(NewLocation);
    }
}

void UGameplayTask_MoveAlongSpline::FinishTask()
{
    GetWorld()->GetTimerManager().ClearTimer(TimerHandle);

    OnMoveFinished.Broadcast(true);

    EndTask();
}
