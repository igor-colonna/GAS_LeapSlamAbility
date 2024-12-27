// Copyright Igorcolonna


#include "AbilitySystem/Abilities/GAS_LeapSlamAbility.h"

#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "AbilitySystem/AbilityTasks/TargetDataUnderMouse.h"
#include "Chaos/Deformable/MuscleActivationConstraints.h"
#include "Character/GASCharacter.h"
#include "Components/SplineComponent.h"

UGAS_LeapSlamAbility::UGAS_LeapSlamAbility()
{
	SplineComp = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComp"));
}



void UGAS_LeapSlamAbility::CreateArc(const FVector& StartPoint, const FVector& EndPoint, float ArcHeight, FVector& OutEnd)
{

	SplineComp->ClearSplinePoints();

	FVector MidPoint = (StartPoint + EndPoint) * 0.5f;
	MidPoint.Z += ArcHeight;
	
	TArray Points = {StartPoint, MidPoint, EndPoint};
	SplineComp->SetSplinePoints(Points, ESplineCoordinateSpace::World, false);
	SplineComp->SetClosedLoop(false, false);
	SplineComp->UpdateSpline();
	OutEnd = EndPoint;
	if(bDebugLines) {DebugLines();}
	
}

FVector UGAS_LeapSlamAbility::CalculatePointWithinRange(
	const FVector& StartLocation,
	const FVector& TargetLocation,
	ECalculatePointResult& Branches,
	FVector& OutLocation,
	UNavigationPath*& OutPath)
{
	if(bDebugLines)
	{
		DrawDebugSphere(GetWorld(), TargetLocation, 500.0f, 30, FColor::Yellow, false, 2.0f);
	}
	
    UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
    if (!NavSys)
    {
    	Branches = ECalculatePointResult::Invalid;
    	OutLocation = StartLocation;
        return StartLocation;
    }
    
    // Find the full path from StartLocation to TargetLocation
    UNavigationPath* NavPath = NavSys->FindPathToLocationSynchronously(GetWorld(), StartLocation, TargetLocation);
    if (!NavPath || !NavPath->IsValid() || NavPath->PathPoints.Num() < 2)
    {
    	UE_LOG(LogTemp, Warning, TEXT("Path inválido ou sem pontos suficientes"));
    	Branches = ECalculatePointResult::Invalid;
    	OutLocation = StartLocation;
        return StartLocation;
    }

	// Verify if the Last Point of the Pathfinding is close enough to the Target Location
	const float DistanceThreshold = 50.f;
	FVector LastPoint = NavPath->PathPoints.Last();
	float DistToTarget = FVector::Dist(LastPoint, TargetLocation);

	if (DistToTarget > DistanceThreshold)
	{
		Branches = ECalculatePointResult::Invalid;
		OutLocation = StartLocation; 
		OutPath = NavPath;
		return StartLocation;
	}

	// Verify if the Navigation path are partial generated
	if (NavPath->IsPartial())
	{
		LastPoint = NavPath->PathPoints.Last();
		if(FVector::Dist(LastPoint, TargetLocation) <= AbilityRange)
		{
			UE_LOG(LogTemp, Warning, TEXT("Caminho parcial: não é possível chegar totalmente ao destino."));
			Branches = ECalculatePointResult::Invalid;
			OutLocation = StartLocation;
			OutPath = NavPath;
			return StartLocation;
		}
	}


	// Calculate the total path to reach the desired location
    float TotalPathDistance = 0.f;
    const TArray<FVector>& PathPoints = NavPath->PathPoints;
    for (int i = 1; i < PathPoints.Num(); i++)
    {
        TotalPathDistance += FVector::Distance(PathPoints[i - 1], PathPoints[i]);
    }

    if (TotalPathDistance <= AbilityRange)
    {
    	Branches = ECalculatePointResult::Valid;
    	OutLocation = TargetLocation;
    	OutPath = NavPath;
        return TargetLocation;
    }

	/*
	 * If the total path is greater than your ability allows,
	 * we will find out at which point on the path we should “stop”
	 * so that the remaining distance to the Target is <= AbilityRange.
	 * In other words, we need to travel (TotalPathDistance - AbilityRange).
	*/
    float DistanceToTravel = TotalPathDistance - AbilityRange;
    float CurrentDistance = 0.f;
    
    FVector ResultLocation = StartLocation;

    // Go through each segment of the path until you find the “end point”
    for (int i = 1; i < PathPoints.Num(); i++)
    {
        float SegmentLength = FVector::Distance(PathPoints[i - 1], PathPoints[i]);

        if (CurrentDistance + SegmentLength >= DistanceToTravel)
        {
            // We find the segment where we can interpolate the "exact point".
            float RemainingDistanceOnSegment = DistanceToTravel - CurrentDistance;
            float Alpha = RemainingDistanceOnSegment / SegmentLength;

            // Interpolats between PathPoints[i-1] and PathPoints[i]
            ResultLocation = FMath::Lerp(PathPoints[i - 1], PathPoints[i], Alpha);
            break;
        }

        CurrentDistance += SegmentLength;
    }

    // Ensures that this point is in a navigable area
    FNavLocation ProjectedNavLoc;
    if (NavSys->ProjectPointToNavigation(ResultLocation, ProjectedNavLoc))
    {
        // Optional debug drawnings
    	if (bDebugLines)
    	{
    		DrawDebugSphere(GetWorld(), ProjectedNavLoc.Location, 20.0f, 30, FColor::Yellow, false, 2.0f);
    	}
	    
    	Branches = ECalculatePointResult::Valid;
    	OutLocation = ProjectedNavLoc.Location;
    	OutPath = NavPath;
	    return ProjectedNavLoc.Location;
    }

	Branches = ECalculatePointResult::Valid;
	OutLocation = ResultLocation;
	OutPath = NavPath;
    return ResultLocation;
}


void UGAS_LeapSlamAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	
	GASCharacter = Cast<AGASCharacter>(GetAvatarActorFromActorInfo());
	if (!GASCharacter)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}

	SetCanBeCanceled(false);
	
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UGAS_LeapSlamAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

}


void UGAS_LeapSlamAbility::DebugLines()
{
	if (UWorld* World = GetWorld())
	{
		
		const float SplineLength = SplineComp->GetSplineLength();
		
		const int32 NumSegments = 10;
		
		FVector LastPos = SplineComp->GetLocationAtDistanceAlongSpline(0.f, ESplineCoordinateSpace::World);
		DrawDebugSphere(World, LastPos, 30, 8, FColor::Red ,false, 1.0);
		for (int32 i = 1; i <= NumSegments; i++)
		{
			float Distance = (SplineLength * i) / NumSegments;
			FVector CurrentPos = SplineComp->GetLocationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);
			DrawDebugLine(
				World, 
				LastPos, 
				CurrentPos, 
				FColor::Green,   
				false,           
				1.f,             
				0,               
				2.f              
			);

			LastPos = CurrentPos;
		}
		DrawDebugSphere(World, LastPos, 30, 8, FColor::Red,false, 1.0);
	}
	
}
