#include "GoldenEgg.h"
#include "Spell.h"
#include "Monster.h"

ASpell::ASpell(const class FObjectInitializer& PCIP) : Super(PCIP)
{
	ProxBox = PCIP.CreateDefaultSubobject<UBoxComponent>(this, TEXT("ProxBox"));
	Particles = PCIP.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("ParticleSystem"));

	// The Particles are the root component, and the ProxBox
	// is a child of the Particle system.
	// If it were the other way around, scaling the ProxBox
	// would also scale the Particles, which we don't want
	RootComponent = Particles;
	ProxBox->AttachTo( RootComponent );

	Duration = 3;
	DamagePerSecond = 1;
	TimeAlive = 0;

	PrimaryActorTick.bCanEverTick = true;
}

void ASpell::SetCaster( AActor *caster )
{
	Caster = caster;
	AttachRootComponentTo( caster->GetRootComponent() );
}

void ASpell::Tick( float DeltaSeconds )
{
	Super::Tick( DeltaSeconds );

	// search the proxbox for all actors in the volume.
	TArray<AActor*> actors;
	ProxBox->GetOverlappingActors( actors );

	// damage each actor the sphere overlaps
	for( int c = 0; c < actors.Num(); c++ )
	{
		// don't damage the spell caster
		if( actors[ c ] != Caster )
		{
			// Only apply the damage if the box is overlapping the actors ROOT component.
			// This way damage doesn't get applied for simply overlapping the SightSphere.
			AMonster *monster = Cast<AMonster>( actors[c] );
			
			if( monster && ProxBox->IsOverlappingComponent( monster->GetCapsuleComponent() ) )
			{
				actors[ c ]->TakeDamage( DamagePerSecond*DeltaSeconds, FDamageEvent(), 0, this );
			}
		}
	}
	
	TimeAlive += DeltaSeconds;
	if( TimeAlive > Duration )
	{
		Destroy();
	}
}
