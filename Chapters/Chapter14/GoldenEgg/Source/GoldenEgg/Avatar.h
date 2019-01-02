#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Avatar.generated.h"

class APickupItem; //  forward declare the APickupItem class, 
				   // since it will be "mentioned" in a member function decl below

UCLASS()
class GOLDENEGG_API AAvatar : public ACharacter
{
	GENERATED_BODY()

public:
	// A map for the player's backpack 
	TMap<FString, int> Backpack;

	// The icons for the items in the backpack, lookup by string 
	TMap<FString, UTexture2D*> Icons;

	// A flag alerting us the UI is showing 
	bool inventoryShowing;
	// member function for letting the avatar have an item 
	void Pickup(APickupItem *item);
	void ToggleInventory();
	void MouseClicked();
	// Sets default values for this character's properties
	AAvatar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// New! These 2 new member function declarations 
	// they will be used to move our player around! 
	void MoveForward(float amount);
	void MoveRight(float amount);

	void Yaw(float amount);
	void Pitch(float amount);

	float Hp;
	float MaxHp;

	FVector knockback;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	void CastSpell(UClass* bpSpell);

	TMap<FString, UClass*> Spells;

	void MouseRightClicked();
};