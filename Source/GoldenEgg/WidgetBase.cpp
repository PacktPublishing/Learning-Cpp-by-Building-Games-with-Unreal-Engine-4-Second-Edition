// Fill out your copyright notice in the Description page of Project Settings.

#include "WidgetBase.h"
#include "Avatar.h"
#include "Kismet/GameplayStatics.h"

bool UWidgetBase::Initialize()
{
	bool success = Super::Initialize();
	if (!success)  return false;

	if (CloseButton != NULL)
	{
		CloseButton->OnClicked.AddDynamic(this, &UWidgetBase::CloseWindow);
	}

	return true;
}

void UWidgetBase::NativeConstruct()
{
	isOpen = true;
}

void UWidgetBase::CloseWindow()
{
	if (isOpen)
	{
		AAvatar *avatar = Cast<AAvatar>(
			UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

		avatar->ToggleInventory();
		isOpen = false;
	}
}