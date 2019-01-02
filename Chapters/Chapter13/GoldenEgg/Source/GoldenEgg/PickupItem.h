#pragma once

#include "GameFramework/Actor.h"
#include "PickupItem.generated.h"

class AMyHUD;

UCLASS()
class GOLDENEGG_API APickupItem : public AActor
{
	GENERATED_UCLASS_BODY()

	// The name of the item you are getting
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	FString Name;

	// How much you are getting
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	int32 Quantity;

	// the sphere you collide with to pick item up
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Item)
	USphereComponent* ProxSphere;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Item)
	UStaticMeshComponent* Mesh;
	
	// The icon that represents the object in UI/canvas
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	UTexture2D* Icon;

	// If this item casts a spell when used, set it here
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	UClass* Spell;

	UFUNCTION(BlueprintNativeEvent, Category = Item)
	void Prox( AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult );
	
};
