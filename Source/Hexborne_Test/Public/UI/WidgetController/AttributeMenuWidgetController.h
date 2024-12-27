// Copyright Igorcolonna

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/GASWidgetController.h"
#include "AttributeMenuWidgetController.generated.h"

class UAttributeInfo;
struct FGASAttributeInfo;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSecondaryAttributeChangedSignature, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeInfoSignature, const FGASAttributeInfo&, Info);

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class HEXBORNE_TEST_API UAttributeMenuWidgetController : public UGASWidgetController
{
	GENERATED_BODY()

	public:

	virtual void BindCallbackToDependencies() override;
	virtual void BroadcastInitialValues() override;
	
	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes Info")
	FAttributeInfoSignature AttributeInfoDelegate;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UAttributeInfo> AttributeInfo;


private:

	//Helper function to broadcast attributes alternative solution
	void BroadcastAttributeInfo(const FGameplayTag& Tag) const;

	//Original Solution
	void BroadcastAttributeInfoOrg(const FGameplayTag& AttributeTag, const FGameplayAttribute& Attribute) const;
};
