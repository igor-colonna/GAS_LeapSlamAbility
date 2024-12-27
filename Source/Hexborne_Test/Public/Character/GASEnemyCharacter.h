// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/GASCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "GASEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class HEXBORNE_TEST_API AGASEnemyCharacter : public AGASCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()
	
public:
	AGASEnemyCharacter();
	
protected:
	virtual void BeginPlay() override;

	virtual void InitAbilityActorInfo() override;
	
public:
	/* Enemy Interface */
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	/* End Enemy Interface */

	/* Combat Interface */
	virtual int32 GetPlayerLevel() override;
	/* End Combat Interface */

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	int32 Level = 1;
};
