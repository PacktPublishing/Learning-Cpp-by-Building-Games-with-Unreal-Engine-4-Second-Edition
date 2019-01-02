#include "GoldenEgg.h"
#include "MyHUD.h"
#include "Avatar.h"

AMyHUD::AMyHUD(const class FObjectInitializer& PCIP) : Super(PCIP)
{
	heldWidget = 0;
}

void AMyHUD::MouseClicked()
{
	FVector2D mouse;

	APlayerController *PController = GetWorld()->GetFirstPlayerController();
	PController->GetMousePosition( mouse.X, mouse.Y );
	//debug( 0, FColor::Yellow,
	//	FString::Printf( TEXT("mouse @ %f %f"), mouse.X, mouse.Y ) );
	// go and see if hit any widgets
	for( int c = 0; c < widgets.Num(); c++ )
	{
		if( widgets[c].hit( mouse ) )
		{
			heldWidget = &widgets[c];
			return;
		}
	}
}

void AMyHUD::MouseRightClicked()
{
	FVector2D mouse;
	APlayerController *PController = GetWorld()->GetFirstPlayerController();
	PController->GetMousePosition( mouse.X, mouse.Y );
	for( int c = 0; c < widgets.Num(); c++ )
	{
		if( widgets[c].hit( mouse ) )
		{
			AAvatar *avatar = Cast<AAvatar>( UGameplayStatics::GetPlayerPawn(GetWorld(), 0) );
			//avatar->Drop( widgets[c].className );
			if( widgets[c].bpSpell )
				avatar->CastSpell( widgets[c].bpSpell );
		}
	}
}

void AMyHUD::MouseMoved()
{
	APlayerController *PController = GetWorld()->GetFirstPlayerController();
	float time = PController->GetInputKeyTimeDown( EKeys::LeftMouseButton );

	static FVector2D lastMouse;
	FVector2D thisMouse, dMouse;
	PController->GetMousePosition( thisMouse.X, thisMouse.Y );
	dMouse = thisMouse - lastMouse;

	if( time > 0.f && heldWidget )
	{
		// the mouse is being held down.
		// move the widget by displacement amt
		heldWidget->pos.X += dMouse.X;
		heldWidget->pos.Y += dMouse.Y; // y inverted
	}

	lastMouse = thisMouse;
}

void AMyHUD::DrawMessages()
{
	// iterate from back to front thru the list, so if we remove
	// an item while iterating, there won't be any problems
	for( int c = messages.Num() - 1; c >= 0; c-- )
	{
		// draw the background box the right size for the message
		float ow, oh, pad=10.f;
		GetTextSize( messages[c].message, ow, oh, hudFont, 1.f );

		float messageH = oh + 2*pad;
		float x = 0, y = c*messageH;
		
		if( messages[c].tex )
		{
			DrawTexture( messages[c].tex, x, y, messageH, messageH, 0, 0, 1, 1 );
		}
		else
		{
			DrawRect( FLinearColor::Red, x, y, messageH, messageH );
		}
		x += messageH;

		DrawRect( messages[c].backColor, x, y, Canvas->SizeX, messageH );
		DrawText( messages[c].message, messages[c].frontColor, x + pad, y + pad, hudFont );

		// reduce lifetime by the time that passed since last frame.
		messages[c].time -= GetWorld()->GetDeltaSeconds();
		// if the message's time is up, remove it
		if( messages[c].time < 0 )
		{
			messages.RemoveAt( c );
		}
	}
}

void AMyHUD::DrawWidgets()
{
	for( int c = 0; c < widgets.Num(); c++ )
	{
		DrawTexture( widgets[c].icon.tex, widgets[c].pos.X, widgets[c].pos.Y,
			widgets[c].size.X, widgets[c].size.Y, 0, 0, 1, 1 );
		// draws relative to center.. don't want to use this version
		//DrawText( icons[c].name, pos, hudFont, FVector2D(.6f, .6f), FColor::Yellow );
		DrawText( widgets[c].icon.name, FLinearColor::Yellow,
			widgets[c].pos.X, widgets[c].pos.Y,
			hudFont, .6f, false );
	}	
}

void AMyHUD::DrawHealthbar()
{
	// Draw the healthbar.
	AAvatar *avatar = Cast<AAvatar>( UGameplayStatics::GetPlayerPawn(GetWorld(), 0) );

	float barWidth=200, barHeight=50, barPad=12, barMargin=50;
	float percHp = avatar->Hp / avatar->MaxHp;
	DrawRect( FLinearColor( 0, 0, 0, 1 ), Canvas->SizeX - barWidth - barPad - barMargin,
		Canvas->SizeY - barHeight - barPad - barMargin, barWidth + 2*barPad, barHeight + 2*barPad );
	DrawRect( FLinearColor( 1-percHp, percHp, 0, 1 ), Canvas->SizeX - barWidth - barMargin,
		Canvas->SizeY - barHeight - barMargin, barWidth*percHp, barHeight );

}

void AMyHUD::DrawHUD()
{
	Super::DrawHUD();

	// dims only exist here in stock variable Canvas
	// Update them so use in addWidget()
	dims.X = Canvas->SizeX;
	dims.Y = Canvas->SizeY;

	DrawMessages();
	DrawWidgets();
	DrawHealthbar();
	
}

void AMyHUD::debug( int slot, FColor color, FString mess )
{
	if( GEngine )
	{
		GEngine->AddOnScreenDebugMessage( slot, 5.f, color, mess );
	}
}

void AMyHUD::addMessage( Message msg )
{
	messages.Add( msg );
}

void AMyHUD::clearWidgets()
{
	widgets.Empty();
}

void AMyHUD::addWidget( Widget widget )
{
	// find the pos of the widget based on the grid.
	// draw the icons..
	FVector2D start( 200, 200 ), pad( 12, 12 );
	widget.size = FVector2D( 100, 100 );
	widget.pos = start;

	// compute the position here
	for( int c = 0; c < widgets.Num(); c++ )
	{
		// Move the position to the right a bit.
		widget.pos.X += widget.size.X + pad.X;

		// If there is no more room to the right then
		// jump to the next line
		if( widget.pos.X + widget.size.X > dims.X )
		{
			widget.pos.X = start.X;
			widget.pos.Y += widget.size.Y + pad.Y;
		}
	}
	
	widgets.Add( widget );
}

