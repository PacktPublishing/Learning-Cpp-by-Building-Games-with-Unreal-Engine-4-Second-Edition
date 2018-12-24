// Fill out your copyright notice in the Description page of Project Settings.

#include "MyHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Avatar.h"

void AMyHUD::DrawHUD()
{
	Super::DrawHUD();
	// dims only exist here in stock variable Canvas 
	// Update them so use in addWidget() 
	const FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	dims.X = ViewportSize.X;
	dims.Y = ViewportSize.Y;
	// Move to DrawMessages();
	// iterate from back to front thru the list, so if we remove 
	// an item while iterating, there won't be any problems 
	for (int c = messages.Num() - 1; c >= 0; c--)
	{
		// draw the background box the right size 
		// for the message 
		float outputWidth, outputHeight, pad = 10.f;
		GetTextSize(messages[c].message, outputWidth, outputHeight,
			hudFont, 1.f);

		float messageH = outputHeight + 2.f*pad;
		float x = 0.f, y = c * messageH;

		// black backing 
		DrawRect(FLinearColor::Black, x, y, Canvas->SizeX, messageH);
		// draw our message using the hudFont 
		DrawText(messages[c].message, messages[c].color, x + pad, y +
			pad, hudFont);

		// reduce lifetime by the time that passed since last  
		// frame. 
		messages[c].time -= GetWorld()->GetDeltaSeconds();

		// if the message's time is up, remove it 
		if (messages[c].time < 0)
		{
			messages.RemoveAt(c);
		}
	}
	DrawWidgets();
}

void AMyHUD::addMessage(Message msg)
{
	messages.Add(msg);
}

void AMyHUD::DrawHealthbar()
{
	// Draw the healthbar. 
	AAvatar *avatar = Cast<AAvatar>(
       UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	float barWidth = 200, barHeight = 50, barPad = 12, barMargin = 50;
	float percHp = avatar->Hp / avatar->MaxHp;
	const FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	DrawRect(FLinearColor(0, 0, 0, 1), ViewportSize.X - barWidth -
		barPad - barMargin, ViewportSize.Y - barHeight - barPad -
		barMargin, barWidth + 2 * barPad, barHeight + 2 * barPad);  
	DrawRect(FLinearColor(1 - percHp, percHp, 0, 1), ViewportSize.X
			- barWidth - barMargin, ViewportSize.Y - barHeight - barMargin,
			barWidth*percHp, barHeight);
}

void AMyHUD::DrawWidgets()
{
	for (int c = 0; c < widgets.Num(); c++)
	{
		Inventory->AddWidget(c, widgets[c].icon.name, widgets[c].icon.tex);
	}
}

void AMyHUD::addWidget(Widget widget)
{
	widgets.Add(widget);
}

void AMyHUD::clearWidgets()
{
	widgets.Empty();
}

void AMyHUD::MouseClicked(int idx)
{
	AAvatar *avatar = Cast<AAvatar>(
		UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (widgets[idx].bpSpell)
	{
		avatar->CastSpell(widgets[idx].bpSpell);
		UGameplayStatics::PlaySound2D(this, audioCue);
	}

}

void AMyHUD::OpenInventory()
{
	if (!Inventory)
	{
		Inventory = CreateWidget<UInventoryWidget>(GetOwningPlayerController(), wInventory);
	}
	Inventory->AddToViewport();
	Inventory->HideWidgets();
}

void AMyHUD::CloseInventory()
{
	clearWidgets();
	if (Inventory)
	{
		Inventory->HideWidgets();
		Inventory->RemoveFromViewport();
	}
}