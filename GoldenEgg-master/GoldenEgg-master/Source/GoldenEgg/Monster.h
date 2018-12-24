// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/SphereComponent.h"
#include "MeleeWeapon.h"
#include "Monster.generated.h"

UCLASS()
class GOLDENEGG_API AMonster : public ACharacter
{
	GENERATED_BODY()
public:
	AMonster(const FObjectInitializer& ObjectInitializer);
	virtual void Tick(float DeltaSeconds) override;

	inline bool isInSightRange(float d)
	{
		return d < SightSphere->GetScaledSphereRadius();
	}

	UFUNCTION(BlueprintCallable, Category = Collision)
	inline bool isInAttackRange(float d)
	{
		return d < AttackRangeSphere->GetScaledSphereRadius();
	}

	// How fast he is 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category =
		MonsterProperties)
		float Speed;

	// The hitpoints the monster has 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category =
		MonsterProperties)
		float HitPoints;

	// Experience gained for defeating 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category =
		MonsterProperties)
		int32 Experience;

	// Blueprint of the type of item dropped by the monster 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category =
		MonsterProperties)
		UClass* BPLoot;

	// The amount of damage attacks do 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category =
		MonsterProperties)
		float BaseAttackDamage;

	// Amount of time the monster needs to rest in seconds 
	// between attacking 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category =
		MonsterProperties)
		float AttackTimeout;

	// Time since monster's last strike, readable in blueprints 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category =
		MonsterProperties)
		float TimeSinceLastStrike;

	// Range for his sight 
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category =
		Collision)
		USphereComponent* SightSphere;

	// Range for his attack. Visualizes as a sphere in editor, 
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category =
		Collision)
		USphereComponent* AttackRangeSphere;

	// The MeleeWeapon class the monster uses 
// If this is not set, he uses a melee attack 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category =
		MonsterProperties)
		UClass* BPMeleeWeapon;

	// The MeleeWeapon instance (set if the character is using 
	// a melee weapon) 
	AMeleeWeapon* MeleeWeapon;

	virtual void PostInitializeComponents() override;

	UFUNCTION(BlueprintCallable, Category = Collision)
		void SwordSwung();

	// The blueprint of the bullet class the monster uses 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category =
		MonsterProperties)
		UClass* BPBullet;
	// Thrust behind bullet launches 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category =
		MonsterProperties)
		float BulletLaunchImpulse;

	void Attack(AActor* thing);

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		class UBehaviorTree* BehaviorTree;
};