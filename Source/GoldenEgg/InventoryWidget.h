// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WidgetBase.h"
#include "UMG/Public/Components/Image.h"
#include "UMG/Public/Components/TextBlock.h"
#include "UMG/Public/Components/Button.h"
#include "InventoryWidget.generated.h"

/**
 *
 */
UCLASS()
class GOLDENEGG_API UInventoryWidget : public UWidgetBase
{
	GENERATED_BODY()

public:
	const int kNumWidgets = 2;
	//image widgets
	UPROPERTY(meta = (BindWidget))
		UImage* InventoryImage1;

	UPROPERTY(meta = (BindWidget))
		UImage* InventoryImage2;

	//text widgets
	UPROPERTY(meta = (BindWidget))
		UTextBlock* InventoryText1;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* InventoryText2;

	//Invisible Buttons
	UPROPERTY(meta = (BindWidget))
		UButton* InventoryButton1;

	UPROPERTY(meta = (BindWidget))
		UButton* InventoryButton2;

	bool Initialize();

	void HideWidgets();
	void AddWidget(int idx, FString name, UTexture2D* img);

	UFUNCTION(BlueprintCallable)
		void MouseClicked1();
	UFUNCTION(BlueprintCallable)
		void MouseClicked2();
};