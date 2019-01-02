#include "GoldenEgg.h"
#include "SpellForceField.h"
#include "Monster.h"

ASpellForceField::ASpellForceField(const class FObjectInitializer& PCIP) : Super(PCIP)
{
	ProxSphere = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("ProxSphere"));
	ProxSphere->AttachTo( Particles );
	Force = 1000;
}

void ASpellForceField::Tick( float DeltaSeconds )
{
	// push everything inside the sphere radially
	Super::Tick( DeltaSeconds );

	// search the proxbox for all actors in the volume.
	TArray<AActor*> actors;
	ProxSphere->GetOverlappingActors( actors );

	// damage each actor the sphere overlaps
	for( int c = 0; c < actors.Num(); c++ )
	{
		// don't damage the spell caster
		if( actors[ c ] != Caster )
		{
			// Only apply the damage if the box is overlapping the actors ROOT component.
			// This way damage doesn't get applied for simply overlapping the SightSphere.
			AMonster *monster = Cast<AMonster>( actors[c] );
			
			if( monster && ProxSphere->IsOverlappingComponent( monster->GetCapsuleComponent() ) )
			{
				FVector toMonster = monster->GetActorLocation() - GetActorLocation();
				toMonster.Normalize();
				monster->Knockback += toMonster*500;
			}
		}
	}
	
	TimeAlive += DeltaSeconds;
	if( TimeAlive > Duration )
	{
		Destroy();
	}
}
