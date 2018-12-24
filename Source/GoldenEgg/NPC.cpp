// Fill out your copyright notice in the Description page of Project Settings.

#include "NPC.h"
#include "Avatar.h"
#include "MyHud.h"

ANPC::ANPC(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    ProxSphere = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this,
        TEXT("Proximity Sphere"));
    ProxSphere->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
    ProxSphere->SetSphereRadius(32.0f);
    // Code to make ANPC::Prox() run when this proximity sphere 
    // overlaps another actor. 
    ProxSphere->OnComponentBeginOverlap.AddDynamic(this, &ANPC::Prox);
    NpcMessage = "Hi, I'm Owen";//default message, can be edited 
                                // in blueprints 
}

// Note! Although this was declared ANPC::Prox() in the header, 
// it is now ANPC::Prox_Implementation here. 
int ANPC::Prox_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{ 
	// if the overlapped actor is not the player, 
	// you should just simply return from the function 
	if( Cast<AAvatar>( OtherActor ) == nullptr ) { 
		return -1; 
	} 
	APlayerController* PController = GetWorld()->GetFirstPlayerController(); 
	if( PController ) 
	{ 
		AMyHUD * hud = Cast<AMyHUD>( PController->GetHUD() ); 
		hud->addMessage( Message( NpcMessage, 5.f, FColor::White ) ); 
	} 
	return 0;
} 
// Called when the game starts or when spawned
void ANPC::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

