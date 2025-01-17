// Copyright Igorcolonna

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "GASAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class HEXBORNE_TEST_API UGASAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:

	static UGASAssetManager& Get();

protected:

	virtual void StartInitialLoading() override;
};
