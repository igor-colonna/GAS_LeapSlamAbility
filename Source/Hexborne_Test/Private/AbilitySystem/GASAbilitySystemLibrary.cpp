// Copyright Igorcolonna


#include "AbilitySystem/GASAbilitySystemLibrary.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/GASAttributeSet.h"
#include "Kismet/GameplayStatics.h"
#include "Player/GASPlayerState.h"
#include "UI/HUD/GASHUD.h"
#include "UI/WidgetController/GASWidgetController.h"

UOverlayWidgetController* UGASAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{

	 if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	 {
		 if(AGASHUD* GASHUD = Cast<AGASHUD>(PC->GetHUD()))
		 {
		 	AGASPlayerState* PS = PC->GetPlayerState<AGASPlayerState>();
		 	UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
		    UAttributeSet* AS = PS->GetAttributeSet();
		 	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
		 	return GASHUD->GetOverlayWidgetController(WidgetControllerParams);
		 }
	 }
	return nullptr;
}

UAttributeMenuWidgetController* UGASAbilitySystemLibrary::GetAttributeMenuWidgetController(
	const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if(AGASHUD* GASHUD = Cast<AGASHUD>(PC->GetHUD()))
		{
			AGASPlayerState* PS = PC->GetPlayerState<AGASPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
			return GASHUD->GetAttributeMenuWidgetController(WidgetControllerParams);
		}
	}
	return nullptr;
}
