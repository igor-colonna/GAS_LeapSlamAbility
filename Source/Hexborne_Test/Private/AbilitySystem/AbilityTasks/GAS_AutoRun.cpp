// Copyright Igorcolonna


#include "AbilitySystem/AbilityTasks/GAS_AutoRun.h"

#include "NavigationPath.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"
#include "GameFramework/Pawn.h"


UGAS_AutoRun::UGAS_AutoRun(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bTickingTask = true; // Habilita Tick
	bIsCompleted = false;
	AutoRunAcceptanceRadius = 50.f;
}

UGAS_AutoRun* UGAS_AutoRun::CreateAutoRunTask(
	UGameplayAbility* OwningAbility,
	const FVector& Destination, 
	USplineComponent* Spline,
	UNavigationPath* Path,
	float AcceptanceRadius,
	bool bDebugLines)
{
	UGAS_AutoRun* Task = NewAbilityTask<UGAS_AutoRun>(OwningAbility);
	Task->CachedDestination = Destination;
	Task->Spline = Spline;
	Task->Path = Path;
	Task->AutoRunAcceptanceRadius = AcceptanceRadius;
	Task->bDebugLines = bDebugLines;
	return Task;
	
}

void UGAS_AutoRun::Activate()
{
	Super::Activate();

	Spline->ClearSplinePoints(true);
	
	// Create a spline with NavPath points
	for(const FVector& PointLoc:Path->PathPoints)
	{
		Spline->AddSplinePoint(PointLoc, ESplineCoordinateSpace::World);
		if(bDebugLines)
		{
			DrawDebugSphere(GetWorld(), PointLoc, 10, 8, FColor::Red, false, 2.f);
		}
	}

	if(bDebugLines)
	{
		DebugLines();
	}
	
	bIsCompleted = false;
}

void UGAS_AutoRun::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);
	
	if (!Spline || !GetAvatarActor())
	{
		EndTask();
		return;
	}

	APawn* ControlledPawn = Cast<APawn>(GetAvatarActor());
	if (!ControlledPawn)
	{
		EndTask();
		return;
	}

	// Keeps moving the player to the nearest spline point until he reaches the last point
	const FVector LocationOnSpline = Spline->FindLocationClosestToWorldLocation(
		ControlledPawn->GetActorLocation(), ESplineCoordinateSpace::World);
	const FVector Direction = Spline->FindDirectionClosestToWorldLocation(LocationOnSpline, ESplineCoordinateSpace::World);
	
	ControlledPawn->AddMovementInput(Direction);
	
	const float DistanceToDestination = FVector::Dist(LocationOnSpline, CachedDestination);
	if (DistanceToDestination <= AutoRunAcceptanceRadius)
	{
		bIsCompleted = true;
		OnCompleted.Broadcast();
		EndTask();
	}
}

void UGAS_AutoRun::DebugLines()
{
	if (UWorld* World = GetWorld())
	{
		
		const float SplineLength = Spline->GetSplineLength();
		
		const int32 NumSegments = 10;
		
		FVector LastPos = Spline->GetLocationAtDistanceAlongSpline(0.f, ESplineCoordinateSpace::World);
		DrawDebugSphere(World, LastPos, 30, 8, FColor::Red ,false, 1.0);
		for (int32 i = 1; i <= NumSegments; i++)
		{
			float Distance = (SplineLength * i) / NumSegments;
			FVector CurrentPos = Spline->GetLocationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);
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