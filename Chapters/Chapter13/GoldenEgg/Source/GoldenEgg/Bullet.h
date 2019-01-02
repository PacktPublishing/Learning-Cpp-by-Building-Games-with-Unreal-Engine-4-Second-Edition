#pragma once

#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class GOLDENEGG_API ABullet : public AActor
{
	GENERATED_UCLASS_BODY()

	// How much damage the bullet does.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Properties)
	float Damage;

	AActor* Firer;

	// the sphere you collide with to do impact damage
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Collision)
	USphereComponent* ProxSphere;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Collision)
	UStaticMeshComponent* Mesh;

	UFUNCTION(BlueprintNativeEvent, Category = Collision)
	void Prox( AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult );
	
};
