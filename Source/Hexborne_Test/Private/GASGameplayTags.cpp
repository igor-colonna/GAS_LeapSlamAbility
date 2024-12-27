// Copyright Igorcolonna


#include "GASGameplayTags.h"
#include "GameplayTagsManager.h"

#define ADDNATIVETAG(AttributeType, AttributeName, Description)									\
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attributes_##AttributeType##_##AttributeName,				\
		*FString((FString("Attributes.") + #AttributeType + FString(".") + #AttributeName)), Description)

ADDNATIVETAG(Primary, Strength, "Increases physical damage and armor resistance")
ADDNATIVETAG(Primary, Intelligence, "Boosts magical damage and mana capacity")
ADDNATIVETAG(Primary, Resilience, "Enhances damage resistance and block chance")
ADDNATIVETAG(Primary, Vigor, "Raises maximum health and health regeneration")

ADDNATIVETAG(Vital, Health, "How much damage the player can take before death")
ADDNATIVETAG(Vital, Mana, "Resource for spells")
ADDNATIVETAG(Vital, MaxHealth, "Defines the player's maximum health")
ADDNATIVETAG(Vital, MaxMana, "Defines the player's maximum mana")
#undef ADDNATIVETAG

FGASGameplayTags FGASGameplayTags::GameplayTags;

void FGASGameplayTags::InitializeNativeGameplayTags()
{
#define ADDTAGTO_CONTAINER(AttributeType, AttributeName) GameplayTags.GASTagsContainer.AddTag(Attributes_##AttributeType##_##AttributeName);

	ADDTAGTO_CONTAINER(Primary, Strength)
	ADDTAGTO_CONTAINER(Primary, Intelligence)
	ADDTAGTO_CONTAINER(Primary, Resilience)
	ADDTAGTO_CONTAINER(Primary, Vigor)

	ADDTAGTO_CONTAINER(Vital, Health)
	ADDTAGTO_CONTAINER(Vital, Mana)
	ADDTAGTO_CONTAINER(Vital, MaxHealth)
	ADDTAGTO_CONTAINER(Vital, MaxMana)

#undef ADDTAGTO_CONTAINER

	/* Input Tags */

	UE_LOG(LogTemp, Warning, TEXT("Input GASGameplayTags Initialized"));
	
	GameplayTags.InputTag_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.LMB"),
		FString("Input Tag for Left Mouse Button")
		);

	GameplayTags.InputTag_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.RMB"),
		FString("Input Tag for Right Mouse Button")
		);
	
	GameplayTags.InputTag_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.1"),
		FString("Input Tag for 1 key")
		);

	GameplayTags.InputTag_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.2"),
		FString("Input Tag for 2 key")
		);

	GameplayTags.InputTag_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.3"),
		FString("Input Tag for 3 key")
		);

	GameplayTags.InputTag_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.4"),
		FString("Input Tag for 4 key")
		);

	GameplayTags.InputTag_WASD = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.WASD"),
		FString("Input Tag for WASD key")
		);
	
}
