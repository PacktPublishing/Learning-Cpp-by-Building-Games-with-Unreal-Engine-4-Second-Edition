// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Canvas.h"
#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

struct Message
{
	FString message;
	float time;
	FColor color;
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
};
