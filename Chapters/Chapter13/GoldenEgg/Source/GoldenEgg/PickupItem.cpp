#include "GoldenEgg.h"
#include "PickupItem.h"
#include "Avatar.h"
#include "MyHUD.h"

APickupItem::APickupItem(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	Name = "UNKNOWN ITEM";
	Quantity = 0;
	Spell = NULL;

	// For pickup items, we want the MESH to simulate the physics and
	// drive the positioning of the object. The reason for that is
	// we want the unique shape of the mesh to determine the object's
	// behavior in the world, not the bounding sphere.
	Mesh = PCIP.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Mesh"));
	RootComponent = Mesh;
	Mesh->SetSimulatePhysics(true);
	
	ProxSphere = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("ProxSphere"));
	// The bounding sphere follows the mesh, so we attach the ProxSphere
	// to the mesh object here.
	ProxSphere->AttachTo( Mesh );
	ProxSphere->OnComponentBeginOverlap.AddDynamic( this, &APickupItem::Prox );
}

void APickupItem::Prox_Implementation( AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult )
{
	// if the overlapped actor is NOT the player, just return.
	if( Cast<AAvatar>( OtherActor ) == nullptr )
	{
		return; // go back, nothing to do here.
	}

	APlayerController* PController = GetWorld()->GetFirstPlayerController();
	AMyHUD* hud = Cast<AMyHUD>( PController->GetHUD() );
	hud->addMessage( Message( Icon, FString("Picked up ") + FString::FromInt(Quantity) +
		FString(" ") + Name, 5.f, FColor::White, FColor::Black ) );
	AAvatar *avatar = Cast<AAvatar>( UGameplayStatics::GetPlayerPawn( GetWorld(), 0 ) );

	// Notice use of keyword this! That is how _this_ Pickup can refer to itself.
	avatar->Pickup( this );

	// delete the pickup item from the level once it is picked up
	Destroy();
}

