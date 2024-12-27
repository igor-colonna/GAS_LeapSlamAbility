// Copyright Igorcolonna

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GASGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class HEXBORNE_TEST_API UGASGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
    

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	FGameplayTag StartupInputTag;
	
};
