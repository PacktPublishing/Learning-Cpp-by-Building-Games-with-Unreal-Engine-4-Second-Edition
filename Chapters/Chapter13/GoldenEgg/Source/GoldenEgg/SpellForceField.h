#pragma once

#include "Spell.h"
#include "SpellForceField.generated.h"

UCLASS()
class GOLDENEGG_API ASpellForceField : public ASpell
{
	GENERATED_UCLASS_BODY()

	// sphere defining volume of force
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Spell)
	USphereComponent* ProxSphere;

	// How much damage the spell does per second
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spell)
	float Force;

	virtual void Tick( float DeltaSeconds ) override;
	
};
