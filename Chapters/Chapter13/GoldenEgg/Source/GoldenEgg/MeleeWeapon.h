#pragma once

#include "GameFramework/Actor.h"
#include "MeleeWeapon.generated.h"

UCLASS()
class GOLDENEGG_API AMeleeWeapon : public AActor
{
	GENERATED_UCLASS_BODY()
	
	// The amount of damage attacks do
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MeleeWeapon)
	float AttackDamage;

	// A list of things the melee weapon already hit this swing?
	// Ensures each thing sword passes thru only gets hit once.
	TArray<AActor*> ThingsHit;
	
	// prevents damage from occurring on frames where the sword is not swinging.
	bool Swinging;

	// "Stop hitting yourself"
	AActor *WeaponHolder;

	// the sphere you collide with to pick item up
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = MeleeWeapon)
	UBoxComponent* ProxBox;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = MeleeWeapon)
	UStaticMeshComponent* Mesh;
	
	UFUNCTION(BlueprintNativeEvent, Category = Collision)
	void Prox( AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult );

	void Swing();
	void Rest();
};
