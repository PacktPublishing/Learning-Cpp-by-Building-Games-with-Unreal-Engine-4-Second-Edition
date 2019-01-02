#pragma once

#include "GameFramework/Character.h"
#include "Monster.generated.h"

class AMeleeWeapon;
class UAnimNotifySwordSwung;

UCLASS()
class GOLDENEGG_API AMonster : public ACharacter
{
	GENERATED_UCLASS_BODY()

	// How fast he is
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
	float Speed;

	// The hitpoints the monster has
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
	float HitPoints;

	// Experience gained for defeating
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
	int32 Experience;

	// The type of item dropped by the monster
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
	UClass* BPLoot;

	// The MeleeWeapon class the monster uses. If this is not set, he uses a melee attack.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
    UClass* BPMeleeWeapon;

	// The amount of damage attacks do, gets added to weapon damage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
	float BaseAttackDamage;

	// Amount of time the monster needs to rest between attacking
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
	float AttackTimeout;

	// The bullet class the monster uses. If this is not set, he uses a melee attack.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
    UClass* BPBullet;

	// Thrust behind bullet launches
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
	float BulletLaunchImpulse;

	AMeleeWeapon* MeleeWeapon;

	// Time since monster's last strike, readable in blueprints
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MonsterProperties)
	float TimeSinceLastStrike;

	// Range for his sight
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Collision)
	USphereComponent* SightSphere;

	// Range for his attack. Visualizes as a sphere in editor,
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Collision)
	USphereComponent* AttackRangeSphere;

	FVector Knockback;
	
	virtual void PostInitializeComponents() override;
	// Each frame, the player gets a Tick() call.
	virtual void Tick(float DeltaSeconds) override;

	void Attack(AActor* thing);
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	inline bool isInAttackRange( float d )
	{ return d < AttackRangeSphere->GetScaledSphereRadius(); }
	inline bool isInSightRange( float d )
	{ return d < SightSphere->GetScaledSphereRadius(); }

	UFUNCTION( BlueprintCallable, Category = Collision )
	bool isInAttackRangeOfPlayer();
	
	UFUNCTION( BlueprintCallable, Category = Collision )
	void SwordSwung();
	
};
