// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/SphereComponent.h"
#include "NPC.generated.h"

UCLASS() class GOLDENEGG_API ANPC : public ACharacter {
	GENERATED_BODY()

public:
	// The sphere that the player can collide with tob
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category =
		Collision)
		USphereComponent* ProxSphere;
	// This is the NPC's message that he has to tell us. 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category =
		NPCMessage)
		FString NpcMessage; // The corresponding body of this function is 
							// ANPC::Prox_Implementation, __not__ ANPC::Prox()! 
							// This is a bit weird and not what you'd expect, 
							// but it happens because this is a BlueprintNativeEvent 
	UFUNCTION(BlueprintNativeEvent, Category = "Collision")
		void Prox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	// You shouldn't need this unless you get a compiler error that it can't find this function.
	virtual int Prox_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Sets default values for this character's properties
	ANPC(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
