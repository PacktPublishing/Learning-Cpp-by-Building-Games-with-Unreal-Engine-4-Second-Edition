// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Monster.h"
#include "Bullet.generated.h"

UCLASS()
class GOLDENEGG_API ABullet : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABullet(const FObjectInitializer& ObjectInitializer);

	// How much damage the bullet does. 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category =
		Properties)
		float Damage;

	// The visible Mesh for the component, so we can see 
	// the shooting object 
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category =
		Collision)
		UStaticMeshComponent* Mesh;

	// the sphere you collide with to do impact damage 
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category =
		Collision)
		USphereComponent* ProxSphere;

	UFUNCTION(BlueprintNativeEvent, Category = Collision)
		void Prox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// You shouldn't need this unless you get a compiler error that it can't find this function.
	virtual int Prox_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	AMonster *Firer;
};