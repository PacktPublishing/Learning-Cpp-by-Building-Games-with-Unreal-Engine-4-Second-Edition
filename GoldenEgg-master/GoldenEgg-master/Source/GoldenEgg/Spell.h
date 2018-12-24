// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "Spell.generated.h"

UCLASS()
class GOLDENEGG_API ASpell : public AActor
{
	GENERATED_BODY()

public:
	ASpell(const FObjectInitializer& ObjectInitializer);

	// box defining volume of damage 
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category =
		Spell)
		UBoxComponent* ProxBox;

	// the particle visualization of the spell 
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category =
		Spell)
		UParticleSystemComponent* Particles;

	// How much damage the spell does per second 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spell)
		float DamagePerSecond;

	// How long the spell lasts 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spell)
		float Duration;

	// Length of time the spell has been alive in the level 
	float TimeAlive;

	// The original caster of the spell (so player doesn't 
	// hit self) 
	AActor* Caster;

	// Parents this spell to a caster actor 
	void SetCaster(AActor* caster);

	// Runs each frame. override the Tick function to deal damage  
	// to anything in ProxBox each frame. 
	virtual void Tick(float DeltaSeconds) override;
};