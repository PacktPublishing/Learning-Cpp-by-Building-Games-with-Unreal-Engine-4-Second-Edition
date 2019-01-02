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
		DrawTexture(widgets[c].icon.tex, widgets[c].pos.X,
			widgets[c].pos.Y, widgets[c].size.X, widgets[c].size.Y, 0, 0, 1, 1);
		DrawText(widgets[c].icon.name, FLinearColor::Yellow,
			widgets[c].pos.X, widgets[c].pos.Y, hudFont, .6f, false);
	}
}


void AMyHUD::addWidget(Widget widget)
{
	// find the pos of the widget based on the grid. 
	// draw the icons.. 
	FVector2D start(200, 200), pad(12, 12);
	widget.size = FVector2D(100, 100);
	widget.pos = start;
	// compute the position here 
	for (int c = 0; c < widgets.Num(); c++)
	{
		// Move the position to the right a bit. 
		widget.pos.X += widget.size.X + pad.X;
		// If there is no more room to the right then 
		// jump to the next line 
		if (widget.pos.X + widget.size.X > dims.X)
		{
			widget.pos.X = start.X;
			widget.pos.Y += widget.size.Y + pad.Y;
		}
	}
	widgets.Add(widget);
}

void AMyHUD::clearWidgets()
{
	widgets.Empty();
}

void AMyHUD::MouseClicked()
{
	FVector2D mouse;
	APlayerController* PController = GetWorld()->GetFirstPlayerController();
	PController->GetMousePosition(mouse.X, mouse.Y);
	heldWidget = NULL; // clear handle on last held widget 
					   // go and see if mouse xy click pos hits any widgets 
	for (int c = 0; c < widgets.Num(); c++)
	{
		if (widgets[c].hit(mouse))
		{
			heldWidget = &widgets[c];// save widget 
			return;                  // stop checking 
		}
	}
}

void AMyHUD::MouseMoved()
{
	static FVector2D lastMouse;
	FVector2D thisMouse, dMouse;
	APlayerController* PController = GetWorld()->GetFirstPlayerController();
	PController->GetMousePosition(thisMouse.X, thisMouse.Y);
	dMouse = thisMouse - lastMouse;
	// See if the left mouse has been held down for 
	// more than 0 seconds. if it has been held down, 
	// then the drag can commence. 
	float time = PController->GetInputKeyTimeDown(
		EKeys::LeftMouseButton);
	if (time > 0.f && heldWidget)
	{
		// the mouse is being held down. 
		// move the widget by displacement amt 
		heldWidget->pos.X += dMouse.X;
		heldWidget->pos.Y += dMouse.Y; // y inverted 
	}
	lastMouse = thisMouse;
}