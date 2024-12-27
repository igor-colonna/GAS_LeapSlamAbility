// Copyright Igorcolonna


#include "AbilitySystem/ModMagCalc/MMC_MaxHealth.h"

#include "AbilitySystem/GASAttributeSet.h"
#include "Interaction/CombatInterface.h"

// Custom Calculation to MaxHealth

UMMC_MaxHealth::UMMC_MaxHealth()
{
	VigorDef.AttributeToCapture = UGASAttributeSet::GetVigorAttribute();
	VigorDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	VigorDef.bSnapshot = false;

	ResilienceDef.AttributeToCapture = UGASAttributeSet::GetResilienceAttribute();
	ResilienceDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	ResilienceDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(VigorDef);
	RelevantAttributesToCapture.Add(ResilienceDef);
}

float UMMC_MaxHealth::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// Gather tags from source and target
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParams;
	EvaluateParams.SourceTags = SourceTags;
	EvaluateParams.TargetTags = TargetTags;

	float Vigor = 0.f;
	float Resilience = 0.f;
	GetCapturedAttributeMagnitude(VigorDef, Spec, EvaluateParams,Vigor);
	GetCapturedAttributeMagnitude(ResilienceDef, Spec, EvaluateParams,Resilience);

	Vigor = FMath::Max<float>(Vigor, 0.f);
	Resilience = FMath::Max<float>(Resilience, 0.f);

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	const int32 PlayerLevel = CombatInterface->GetPlayerLevel();

	return 80.f + (1.f * Vigor) + (0.2f * Resilience) + (10.f * PlayerLevel);
}
