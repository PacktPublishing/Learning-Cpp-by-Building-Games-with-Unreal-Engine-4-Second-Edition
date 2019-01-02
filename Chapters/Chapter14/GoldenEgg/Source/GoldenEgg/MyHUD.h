// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Canvas.h"
#include "GameFramework/HUD.h"
#include "InventoryWidget.h"
#include "Sound/SoundCue.h"
#include "MyHUD.generated.h"

struct Icon
{
	FString name;
	UTexture2D* tex;
	Icon() { name = "UNKNOWN ICON"; tex = 0; }
	Icon(FString& iName, UTexture2D* iTex)
	{
		name = iName;
		tex = iTex;
	}
};

struct Widget
{
	Icon icon;
	// bpSpell is the blueprint of the spell this widget casts 
	UClass *bpSpell;
	Widget(Icon iicon)
	{
		icon = iicon;
	}
};

struct Message
{
	FString message;
	float time;
	FColor color;
	UTexture2D* tex;
	Message()
	{
		// Set the default time. 
		time = 5.f;
		color = FColor::White;
	}
	Message(FString iMessage, float iTime, FColor iColor)
	{
		message = iMessage;
		time = iTime;
		color = iColor;
	}
	Message(UTexture2D* img, FString iMessage, float iTime, FColor iColor)
	{
		tex = img;
		message = iMessage;
		time = iTime;
		color = iColor;
	}
};

/**
 * 
 */
UCLASS()
class GOLDENEGG_API AMyHUD : public AHUD
{
	GENERATED_BODY()
public:
	// The font used to render the text in the HUD. 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUDFont)
		UFont* hudFont;
	// New! An array of messages for display 
	TArray<Message> messages;
	virtual void DrawHUD() override;
	// New! A function to be able to add a message to display 
	void addMessage(Message msg);
	void DrawHealthbar();

	// New! An array of widgets for display 
	TArray<Widget> widgets;

	//Hold screen dimensions
	FVector2D dims;
	void DrawWidgets();

	Widget* heldWidget;  // hold the last touched Widget in memory 

	void MouseClicked(int idx);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
		TSubclassOf<class UUserWidget> wInventory;

	UInventoryWidget* Inventory;

	void OpenInventory();
	void CloseInventory();

	void clearWidgets();
	void addWidget(Widget widget);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
		USoundCue* audioCue;
};