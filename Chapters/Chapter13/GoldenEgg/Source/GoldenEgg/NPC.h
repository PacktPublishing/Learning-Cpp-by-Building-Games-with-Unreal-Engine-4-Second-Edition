// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "NPC.generated.h"

UCLASS()
class GOLDENEGG_API ANPC : public ACharacter
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision)
	USphereComponent* ProxSphere;

	// This is the NPC's name
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NPCMessage)
	FString Name;
	
	// This is the NPC's message that he has to tell us.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NPCMessage)
	FString NpcMessage;
	// When you create a blueprint from this class, you want to be able to edit that message
	// in blueprints, that's why we have the EditAnywhere and BlueprintReadWrite properties.

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NPCMessage)
	UTexture2D* Face;
	
	// The corresponding body of this function is ANPC::Prox_Implementation, 
	// __not__ ANPC::Prox()! This is a bit weird, but it happens because
	// this is a BlueprintNativeEvent
	UFUNCTION(BlueprintNativeEvent, Category = Collision)
	void Prox( AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult );
	
};
