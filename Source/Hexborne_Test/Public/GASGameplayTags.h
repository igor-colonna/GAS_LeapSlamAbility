// Copyright Igorcolonna

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "NativeGameplayTags.h"

UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attributes_Primary_Strength)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attributes_Primary_Intelligence)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attributes_Primary_Resilience)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attributes_Primary_Vigor)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attributes_Vital_MaxHealth)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attributes_Vital_MaxMana)



/**
 *  GASGameplayTags
 *
 *  Singleton containg native Gameplay Tags
 */

struct FGASGameplayTags
{
public:
 static const FGASGameplayTags& Get() {return GameplayTags;}
 static void InitializeNativeGameplayTags();

 FGameplayTagContainer GASTagsContainer = FGameplayTagContainer();

 FGameplayTag InputTag_WASD;
 FGameplayTag InputTag_LMB;
 FGameplayTag InputTag_RMB;
 FGameplayTag InputTag_1;
 FGameplayTag InputTag_2;
 FGameplayTag InputTag_3;
 FGameplayTag InputTag_4;
 


protected:
 static FGASGameplayTags GameplayTags;
};
