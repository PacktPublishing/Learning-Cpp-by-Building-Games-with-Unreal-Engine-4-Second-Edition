#include "GoldenEgg.h"
#include "Bullet.h"

ABullet::ABullet(const class FObjectInitializer& PCIP) : Super(PCIP)
{
	Firer = NULL;

	// We want the bullet to simulate physics using
	// its bounding sphere.
	ProxSphere = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("ProxSphere"));
	RootComponent = ProxSphere;
	ProxSphere->OnComponentBeginOverlap.AddDynamic( this, &ABullet::Prox );
	
	// For the bullet, the mesh is "dumb". It just "tags along"
	// with whatever the ProxSphere is doing, since the ProxSphere
	// is going to respond to collisions with objects.
	// Attach the Mesh to the ProxSphere.
	Mesh = PCIP.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Mesh"));
	Mesh->AttachTo( ProxSphere );
	
	Damage = 1;
}

void ABullet::Prox_Implementation( AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult )
{
	// Don't let a bullet hit the person that shot it.
	if( OtherActor == Firer )
	{
		return;
	}

	if( OtherComp != OtherActor->GetRootComponent() )
	{
		// don't collide w/ anything other than the actor's root component
		return;
	}

	OtherActor->TakeDamage( Damage, FDamageEvent(), NULL, this );

	Destroy();
}

