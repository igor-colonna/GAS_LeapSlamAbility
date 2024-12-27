// Copyright Igorcolonna


#include "AbilitySystem/Data/AttributeInfo.h"

#include "GASGameplayTags.h"
#include "AbilitySystem/GASAttributeSet.h"

// An Asset Manager to attribute a Gameplay tag to each Attribute

FGASAttributeInfo UAttributeInfo::FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLogNotFound) const
{
	for(const FGASAttributeInfo& Info : AttributeInformation)
	{
		if(Info.AttributeTag.MatchesTag(AttributeTag))
		{
			return Info;
		}
	}

	if(bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can`t find info for AttributeTag [%s] on AttributeInfo [%s]"), *AttributeTag.ToString(), *GetNameSafe(this));
	}
	return FGASAttributeInfo();
}

#if WITH_EDITOR
void UAttributeInfo::PopulateDataAsset()
{
	
	const FGASGameplayTags GASGameplayTags = FGASGameplayTags::Get();
	AttributeInformation.Empty();
	AttributeInformation.SetNumZeroed(GASGameplayTags.GASTagsContainer.Num());

	for(int i = 0; i < GASGameplayTags.GASTagsContainer.Num(); ++i)
	{
		UE_LOG(LogTemp, Display, TEXT("UAttributeInfo::PopulateDataAsset"));
		const FGameplayTag IndexTag = GASGameplayTags.GASTagsContainer.GetByIndex(i);
		AttributeInformation[i].AttributeTag = IndexTag;								// Set Attribute Tag

		const FGameplayTagNode* TagNode = UGameplayTagsManager::Get().FindTagNode(IndexTag).Get();	//Get the last node of the Gameplay Tag
		FString NodeString = FName::NameToDisplayString(TagNode->GetSimpleTagName().ToString(), false); // Get node name (i.e. Attribute.Primary.Strength returns Strength) and make display ready
		AttributeInformation[i].AttributeName = FText::FromString(NodeString);		//Set AttributeName

		for(TFieldIterator<FProperty> It(UGASAttributeSet::StaticClass()); It; ++It)
		{
			if(FGameplayAttribute::IsGameplayAttributeDataProperty(*It) && FGameplayAttribute(*It).GetName() == TagNode->GetSimpleTagName().ToString())
			{
				AttributeInformation[i].AttributeToGet = FGameplayAttribute(*It);
				break;
			}
		}

		const FName TagName = IndexTag.GetTagName();

		FString TagComment = FString();
		FName TagSource = FName();
		bool bIsTagExplicit = false;
		bool bIsRestricted = false;
		bool bAllowNonRestrictedChildren = false;

		UGameplayTagsManager::Get().GetTagEditorData(
			TagName,
			TagComment,
			TagSource,
			bIsTagExplicit,
			bIsRestricted,
			bAllowNonRestrictedChildren);
		AttributeInformation[i].AttributeDescription = FText::FromString(TagComment);			// Set AttributeDescripition
	}
}

#endif


