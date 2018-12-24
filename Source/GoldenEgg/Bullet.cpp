// Fill out your copyright notice in the Description page of Project Settings.

#include "Bullet.h"

// Sets default values
ABullet::ABullet(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Mesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this,
		TEXT("Mesh"));
	RootComponent = Mesh;

	ProxSphere = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this,
		TEXT("ProxSphere"));
	ProxSphere->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);

	ProxSphere->OnComponentBeginOverlap.AddDynamic(this,
		&ABullet::Prox);
	Damage = 1;
}

int ABullet::Prox_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherComp != OtherActor->GetRootComponent())
	{
		// don't collide w/ anything other than 
		// the actor's root component 
		return -1;
	}

	OtherActor->TakeDamage(Damage, FDamageEvent(), NULL, this);
	Destroy();
	return 0;
}
