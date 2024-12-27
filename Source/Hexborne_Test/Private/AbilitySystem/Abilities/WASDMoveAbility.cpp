// Copyright Igorcolonna


#include "AbilitySystem/Abilities/WASDMoveAbility.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "Player/GASPlayerController.h"

void UWASDMoveAbility::ActivateAbility(
    const FGameplayAbilitySpecHandle Handle,
    const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo,
    const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
    
}


void UWASDMoveAbility::EndAbility(
    const FGameplayAbilitySpecHandle Handle,
    const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo,
    bool bReplicateEndAbility,
    bool bWasCancelled)
{
    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UWASDMoveAbility::Move()
{
    AActor* Avatar = GetAvatarActorFromActorInfo();
    APawn* Pawn = Cast<APawn>(Avatar);
    AGASPlayerController* PlayerController = Cast<AGASPlayerController>(Pawn->GetController());
    if (!Pawn)
        return;

    Pawn->AddMovementInput(PlayerController->ForwardDirection, PlayerController->InputAxisVector.Y);
    Pawn->AddMovementInput(PlayerController->RightDirection, PlayerController->InputAxisVector.X);
    
}
