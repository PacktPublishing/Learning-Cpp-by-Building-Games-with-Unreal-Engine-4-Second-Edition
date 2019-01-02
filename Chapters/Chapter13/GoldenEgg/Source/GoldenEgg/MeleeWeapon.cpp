#include "GoldenEgg.h"
#include "MeleeWeapon.h"

AMeleeWeapon::AMeleeWeapon(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	ProxBox = PCIP.CreateDefaultSubobject<UBoxComponent>(this, TEXT("ProxBox"));
	RootComponent = ProxBox;
	ProxBox->OnComponentBeginOverlap.AddDynamic( this, &AMeleeWeapon::Prox );

	Mesh = PCIP.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Mesh"));
	Mesh->AttachTo( RootComponent );

	Swinging = false;
	WeaponHolder = NULL;
}

void AMeleeWeapon::Prox_Implementation( AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult )
{
	// don't hit non root components
	if( OtherComp != OtherActor->GetRootComponent() )
	{
		return;
	}

	// avoid hitting yourself, and avoid hitting the same OtherActor twice.
	if( Swinging && OtherActor != WeaponHolder && !ThingsHit.Contains(OtherActor) )
	{
		OtherActor->TakeDamage( AttackDamage, FDamageEvent(), NULL, this );
		ThingsHit.Add( OtherActor );
	}
}

void AMeleeWeapon::Swing()
{
	ThingsHit.Empty();	// empty the list
	Swinging = true;
}

void AMeleeWeapon::Rest()
{
	ThingsHit.Empty();
	Swinging = false;
}