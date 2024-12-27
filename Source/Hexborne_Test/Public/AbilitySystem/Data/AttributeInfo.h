// Copyright Igorcolonna

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AttributeInfo.generated.h"

USTRUCT(BlueprintType)
struct FGASAttributeInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag AttributeTag = FGameplayTag();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttributeName = FText();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttributeDescription = FText();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float AttributeValue = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayAttribute AttributeToGet;
	
};
/**
 * 
 */
UCLASS()
class HEXBORNE_TEST_API UAttributeInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	FGASAttributeInfo FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLogNotFound = false) const;


#if WITH_EDITOR
	UFUNCTION(Category="Populate Attribute Info", CallInEditor)
	void PopulateDataAsset();
#endif

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(TitleProperty="{AttributeName}"))
	TArray<FGASAttributeInfo> AttributeInformation;
	
	
};
