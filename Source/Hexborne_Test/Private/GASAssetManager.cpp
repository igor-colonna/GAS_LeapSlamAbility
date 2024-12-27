// Copyright Igorcolonna


#include "GASAssetManager.h"

#include "AbilitySystemComponent.h"
#include "GASGameplayTags.h"

UGASAssetManager& UGASAssetManager::Get()
{
	check(GEngine);
	
	UGASAssetManager* GASAssetManager = Cast<UGASAssetManager>(GEngine->AssetManager);
	return * GASAssetManager;
	
}

void UGASAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	FGASGameplayTags::InitializeNativeGameplayTags();
	
}
