// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PickupItem.generated.h"

UCLASS()
class GOLDENEGG_API APickupItem : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APickupItem(const FObjectInitializer& ObjectInitializer);

	// The name of the item you are getting 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
		FString Name;

	// How much you are getting 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
		int32 Quantity;

	// the sphere you collide with to pick item up 
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Item)
		USphereComponent* ProxSphere;

	// The mesh of the item 
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Item)
		UStaticMeshComponent* Mesh;
	// The icon that represents the object in UI/canvas 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
		UTexture2D* Icon;
	// When something comes inside ProxSphere, this function runs 
	UFUNCTION(BlueprintNativeEvent, Category = Collision)
		void Prox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	virtual int Prox_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// If this item casts a spell when used, set it here 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
		UClass* Spell;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};