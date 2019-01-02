// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UMG/Public/Components/Button.h"
#include "WidgetBase.generated.h"

/**
 * WidgetBase.h
 */
UCLASS()
class GOLDENEGG_API UWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidgetOptional))
		UButton* CloseButton;

	bool isOpen;

	bool Initialize();
	void NativeConstruct();

	 UFUNCTION(BlueprintCallable)
		void CloseWindow();
};
