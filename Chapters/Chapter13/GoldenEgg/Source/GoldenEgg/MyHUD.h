#pragma once

#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

struct Message
{
	FString message;
	float time;
	FColor frontColor;
	FColor backColor;
	UTexture2D* tex;

	Message()
	{
		// Set the default time.
		time = 5.f;
		frontColor = FColor::White;
		backColor = FColor::Black;
	}

	Message( FString iMessage, float iTime, FColor iFrontColor, FColor iBackColor )
	{
		message = iMessage;
		time = iTime;
		frontColor = iFrontColor;
		backColor = iBackColor;
		tex = 0;
	}

	Message( UTexture2D* iTex, FString iMessage, float iTime, FColor iFrontColor, FColor iBackColor )
	{
		tex = iTex;
		message = iMessage;
		time = iTime;
		frontColor = iFrontColor;
		backColor = iBackColor;
	}
};

struct Icon
{
	FString name;
	UTexture2D* tex;

	Icon(){ name = "UNKNOWN ICON"; tex = 0; }
	Icon( FString& iName, UTexture2D* iTex )
	{
		name = iName;
		tex = iTex;
	}
};

struct Widget
{
	Icon icon;
	// in case you need to drop an item, this is the class the item was from
	UClass *className;
	// bpSpell is the blueprint of the spell this widget casts
	UClass *bpSpell;
	FVector2D pos, size;
	Widget(Icon iicon, UClass *iClassName)
	{
		icon = iicon;
		className = iClassName;
	}
	float left(){ return pos.X; }
	float right(){ return pos.X + size.X; }
	float top(){ return pos.Y; }
	float bottom(){ return pos.Y + size.Y; }
	bool hit( FVector2D v )
	{
		// +---+ top (0)
		// |   |
		// +---+ bottom (2) (bottom > top)
		// L   R
		return v.X > left() && v.X < right() && v.Y > top() && v.Y < bottom();
	}
};

UCLASS()
class GOLDENEGG_API AMyHUD : public AHUD
{
	GENERATED_UCLASS_BODY()

	// The font used to render the text in the HUD.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUDFont)
	UFont* hudFont;

	// The messages available
	TArray<Message> messages;

	// The list of HUD items that are being
	// drawn in the game this frame.
	TArray<Widget> widgets;
	Widget* heldWidget;

	// These are the dims of the screen.
	FVector2D dims;
	
	void MouseClicked();
	void MouseRightClicked();
	void MouseMoved();
	void DrawMessages();
	void DrawWidgets();
	void DrawHealthbar();
	virtual void DrawHUD() override;
	void debug( int slot, FColor color, FString mess );
	void addMessage( Message msg );
	void clearWidgets();
	void addWidget( Widget widget );

};
