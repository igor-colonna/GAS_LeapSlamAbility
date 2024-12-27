// Copyright Igorcolonna


#include "UI/WidgetController/GASWidgetController.h"

void UGASWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WidgetControllerParams)
{
	PlayerController = WidgetControllerParams.PlayerController;
	PlayerState = WidgetControllerParams.PlayerState;
	AbilitySystemComponent = WidgetControllerParams.AbilitySystemComponent;
	AttributeSet = WidgetControllerParams.AttributeSet;
}

void UGASWidgetController::BroadcastInitialValues()
{
	
}

void UGASWidgetController::BindCallbackToDependencies()
{
	
}
