// Copyright Igorcolonna


#include "AbilitySystem/ModMagCalc/MMC_MaxMana.h"

#include "AbilitySystem/GASAttributeSet.h"
#include "Interaction/CombatInterface.h"

// Custom Calculation to MaxHealth

UMMC_MaxMana::UMMC_MaxMana()
{
	VigorDef.AttributeToCapture = UGASAttributeSet::GetVigorAttribute();
	VigorDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	VigorDef.bSnapshot = false;

	IntelligenceDef.AttributeToCapture = UGASAttributeSet::GetIntelligenceAttribute();
	IntelligenceDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	IntelligenceDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(VigorDef);
	RelevantAttributesToCapture.Add(IntelligenceDef);
}

float UMMC_MaxMana::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// Gather tags from source and target
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParams;
	EvaluateParams.SourceTags = SourceTags;
	EvaluateParams.TargetTags = TargetTags;

	float Vigor = 0.f;
	float Intelligence = 0.f;
	GetCapturedAttributeMagnitude(VigorDef, Spec, EvaluateParams,Vigor);
	GetCapturedAttributeMagnitude(IntelligenceDef, Spec, EvaluateParams,Intelligence);

	Vigor = FMath::Max<float>(Vigor, 0.f);
	Intelligence = FMath::Max<float>(Intelligence, 0.f);

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	const int32 PlayerLevel = CombatInterface->GetPlayerLevel();

	return 50.f + (0.2f * Vigor) + (0.9f * Intelligence) + (5.f * PlayerLevel);
}
