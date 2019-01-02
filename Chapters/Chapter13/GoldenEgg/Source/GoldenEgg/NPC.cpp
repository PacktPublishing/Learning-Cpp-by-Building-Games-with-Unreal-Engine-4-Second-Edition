#include "GoldenEgg.h"
#include "NPC.h"
#include "MyHUD.h"
#include "Avatar.h"

ANPC::ANPC(const class FObjectInitializer& PCIP) : Super(PCIP)
{
	ProxSphere = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("ProxSphere"));
	
	// You must attach the ProxSphere to the root component, otherwise,
	// the ProxSphere will NOT be with the NPC!
	ProxSphere->AttachTo( RootComponent );
	ProxSphere->SetSphereRadius( 32.f );

	// Code to make ANPC::Prox() run when this proximity sphere
	// overlaps another actor.
	ProxSphere->OnComponentBeginOverlap.AddDynamic( this, &ANPC::Prox );
	NpcMessage = "Hi, I'm Owen";//default message, can be edited in blueprints
}

void ANPC::Prox_Implementation( AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult )
{
	// if the overlapped actor is the player, display my message for him
	AAvatar *player = Cast<AAvatar>( OtherActor );
	if( player == nullptr )
	{
		// The intersected actor wasn't the player, so ignore this overlap
		return;
	}

	// The player has multiple components inside him. we don't want an overlap event
	// for EACH component, so we just check for intersection with the player's root component.
	if( OtherComp != player->GetRootComponent() )
	{
		return;
	}

	APlayerController* PController = GetWorld()->GetFirstPlayerController();
	AMyHUD * hud = Cast<AMyHUD>( PController->GetHUD() );
	hud->addMessage( Message( Face, Name + FString(": ") + NpcMessage, 5.f, FColor::White, FColor::Black ) );
}