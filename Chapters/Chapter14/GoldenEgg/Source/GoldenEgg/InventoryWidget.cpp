// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryWidget.h"
#include "MyHUD.h"
#include "Runtime/UMG/Public/Components/SlateWrapperTypes.h"

bool UInventoryWidget::Initialize()
{
	bool success = Super::Initialize();
	if (!success)  return false;

	if (InventoryButton1 != NULL)
	{
		InventoryButton1->OnClicked.AddDynamic(this, &UInventoryWidget::MouseClicked1);
	}
	if (InventoryButton2 != NULL)
	{
		InventoryButton2->OnClicked.AddDynamic(this, &UInventoryWidget::MouseClicked2);
	}

	return true;
}

void UInventoryWidget::HideWidgets()
{
	InventoryImage1->SetVisibility(ESlateVisibility::Hidden);
	InventoryText1->SetVisibility(ESlateVisibility::Hidden);
	InventoryImage2->SetVisibility(ESlateVisibility::Hidden);
	InventoryText2->SetVisibility(ESlateVisibility::Hidden);
}

void UInventoryWidget::AddWidget(int idx, FString name, UTexture2D* img)
{
	if (idx < kNumWidgets)
	{
		switch (idx)
		{
		case 0:
			InventoryImage1->SetBrushFromTexture(img);
			InventoryText1->SetText(FText::FromString(name));
			InventoryImage1->SetVisibility(ESlateVisibility::Visible);
			InventoryText1->SetVisibility(ESlateVisibility::Visible);
			break;
		case 1:
			InventoryImage2->SetBrushFromTexture(img);
			InventoryText2->SetText(FText::FromString(name));
			InventoryImage2->SetVisibility(ESlateVisibility::Visible);
			InventoryText2->SetVisibility(ESlateVisibility::Visible);
			break;
		}

	}
}

void UInventoryWidget::MouseClicked1()
{
	// Get the controller & hud 
	APlayerController* PController = GetWorld()->GetFirstPlayerController();
	AMyHUD* hud = Cast<AMyHUD>(PController->GetHUD());
	hud->MouseClicked(0);
}

void UInventoryWidget::MouseClicked2()
{
	// Get the controller & hud 
	APlayerController* PController = GetWorld()->GetFirstPlayerController();
	AMyHUD* hud = Cast<AMyHUD>(PController->GetHUD());
	hud->MouseClicked(1);
}
