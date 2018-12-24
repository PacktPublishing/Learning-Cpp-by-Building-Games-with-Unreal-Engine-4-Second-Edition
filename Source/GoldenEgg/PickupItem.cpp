// Fill out your copyright notice in the Description page of Project Settings.

#include "PickupItem.h"
#include "Avatar.h"
#include "MyHUD.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APickupItem::APickupItem(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Name = "UNKNOWN ITEM";
	Quantity = 0;

	// initialize the unreal objects 
	ProxSphere = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this,
		TEXT("ProxSphere"));
	Mesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this,
		TEXT("Mesh"));

	// make the root object the Mesh 
	RootComponent = Mesh;
	Mesh->SetSimulatePhysics(true);

	// Code to make APickupItem::Prox() run when this 
	// object's proximity sphere overlaps another actor. 
	ProxSphere->OnComponentBeginOverlap.AddDynamic(this, &APickupItem::Prox);
	ProxSphere->AttachToComponent(Mesh, FAttachmentTransformRules::KeepWorldTransform); // very important!              
}

int APickupItem::Prox_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// if the overlapped actor is NOT the player, 
	// you simply should return 
	if (Cast<AAvatar>(OtherActor) == nullptr)
	{
		return -1;
	}

	// Get a reference to the player avatar, to give him 
	// the item 
	AAvatar *avatar = Cast<AAvatar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	// Let the player pick up item 
	// Notice use of keyword this! 
	// That is how _this_ Pickup can refer to itself. 
	avatar->Pickup(this);

	// Get a reference to the controller 
	APlayerController* PController = GetWorld()->GetFirstPlayerController();

	// Get a reference to the HUD from the controller 
	AMyHUD* hud = Cast<AMyHUD>(PController->GetHUD());
	hud->addMessage(Message(Icon, FString("Picked up ") + FString::FromInt(Quantity) + FString(" ") + Name, 5.f, FColor::White)
	);

	Destroy();

	return 0;
}

// Called when the game starts or when spawned
void APickupItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickupItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

