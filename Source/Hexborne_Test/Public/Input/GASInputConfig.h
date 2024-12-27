// Copyright Igorcolonna

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "GASInputConfig.generated.h"

USTRUCT(BlueprintType)
struct FGASInputAction
{ 
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	const class UInputAction* InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag = FGameplayTag();
};

/**
 * 
 */
UCLASS()
class HEXBORNE_TEST_API UGASInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:

	const UInputAction* FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound = false) const;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FGASInputAction> AbilityInputActions;
};
