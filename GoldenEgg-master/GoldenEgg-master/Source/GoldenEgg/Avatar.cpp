// Fill out your copyright notice in the Description page of Project Settings.

#include "Avatar.h"
#include "PickupItem.h"
#include "MyHUD.h"
#include "Spell.h"

// Sets default values
AAvatar::AAvatar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//defaults for testing.
	Hp = 90;
	MaxHp = 100;
}

// Called when the game starts or when spawned
void AAvatar::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAvatar::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// apply knockback vector 
	AddMovementInput(-1*knockback, 1.f);

	// half the size of the knockback each frame 
	knockback *= 0.5f;
}

// Called to bind functionality to input
void AAvatar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Inventory", IE_Pressed, this,
		&AAvatar::ToggleInventory);
	PlayerInputComponent->BindAction("MouseClickedLMB", IE_Pressed, this,
		&AAvatar::MouseClicked);
	PlayerInputComponent->BindAction("MouseClickedRMB", IE_Pressed, this,
		&AAvatar::MouseRightClicked);
	PlayerInputComponent->BindAxis("Forward", this,
		&AAvatar::MoveForward);
	PlayerInputComponent->BindAxis("Strafe", this, &AAvatar::MoveRight);

	PlayerInputComponent->BindAxis("Yaw", this, &AAvatar::Yaw);
	PlayerInputComponent->BindAxis("Pitch", this, &AAvatar::Pitch);

}

void AAvatar::MoveForward(float amount)
{
	// Don't enter the body of this function if Controller is 
	// not set up yet, or if the amount to move is equal to 0 
	if (Controller && amount)
	{
		FVector fwd = GetActorForwardVector();
		// we call AddMovementInput to actually move the 
		// player by `amount` in the `fwd` direction 
		AddMovementInput(fwd, amount);
	}
}

void AAvatar::MoveRight(float amount)
{
	if (Controller && amount)
	{
		FVector right = GetActorRightVector();
		AddMovementInput(right, amount);
	}
}

void AAvatar::Yaw(float amount)
{
	//x axis 
	if (inventoryShowing)
	{
		// When the inventory is showing, 
		// pass the input to the HUD 
		APlayerController* PController = GetWorld()->GetFirstPlayerController();
		return;
	}
	else
	{
		AddControllerYawInput(200.f*amount * GetWorld()->GetDeltaSeconds());
	}
}
void AAvatar::Pitch(float amount)
{
	if (inventoryShowing)
	{
		// When the inventory is showing, 
		// pass the input to the HUD 
		APlayerController* PController = GetWorld()->GetFirstPlayerController();
		return;
	}
	else
	{ 
		AddControllerPitchInput(200.f * amount * GetWorld()->GetDeltaSeconds());
	}
}

void AAvatar::Pickup(APickupItem *item)
{
	if (Backpack.Find(item->Name))
	{
		// the item was already in the pack.. increase qty of it 
		Backpack[item->Name] += item->Quantity;
	}
	else
	{
		// the item wasn't in the pack before, add it in now 
		Backpack.Add(item->Name, item->Quantity);
		// record ref to the tex the first time it is picked up 
		Icons.Add(item->Name, item->Icon);
		// the spell associated with the item 
		Spells.Add(item->Name, item->Spell);
	}
}

void AAvatar::ToggleInventory()
{
	// Get the controller & hud 
	APlayerController* PController = GetWorld()->GetFirstPlayerController();
	AMyHUD* hud = Cast<AMyHUD>(PController->GetHUD());

	// If inventory is displayed, undisplay it. 
	if (inventoryShowing)
	{
		hud->CloseInventory();
		inventoryShowing = false;
		PController->bShowMouseCursor = false;
		return;
	}

	// Otherwise, display the player's inventory 
	inventoryShowing = true;
	PController->bShowMouseCursor = true;
	hud->OpenInventory();
	for (TMap<FString, int>::TIterator it =
		Backpack.CreateIterator(); it; ++it)
	{
		// Combine string name of the item, with qty eg Cow x 5 
		FString fs = it->Key + FString::Printf(TEXT(" x %d"), it->Value);
		UTexture2D* tex;
		if (Icons.Find(it->Key))
		{
			tex = Icons[it->Key];
			Widget w(Icon(fs, tex));
			w.bpSpell = Spells[it->Key];
			hud->addWidget(w);
		}
	}
	hud->DrawWidgets();
}

void AAvatar::MouseClicked()
{
	APlayerController* PController = GetWorld()->GetFirstPlayerController();
}

float AAvatar::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	// add some knockback that gets applied over a few frames 
	knockback = GetActorLocation() - DamageCauser->GetActorLocation();
	knockback.Normalize();
	knockback *= DamageAmount * 500; // knockback proportional to damage 
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void AAvatar::CastSpell(UClass* bpSpell)
{
	// instantiate the spell and attach to character 
	ASpell *spell = GetWorld()->SpawnActor<ASpell>(bpSpell,
		FVector(0), FRotator(0));

	if (spell)
	{
		spell->SetCaster(this);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Yellow,
			FString("can't cast ") + bpSpell->GetName());
	}
}

void AAvatar::MouseRightClicked()
{
	if (inventoryShowing)
	{
		APlayerController* PController = GetWorld()->GetFirstPlayerController();
	}
}