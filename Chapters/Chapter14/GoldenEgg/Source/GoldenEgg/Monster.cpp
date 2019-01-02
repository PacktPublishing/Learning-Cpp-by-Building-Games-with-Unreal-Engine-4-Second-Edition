// Fill out your copyright notice in the Description page of Project Settings.

#include "Monster.h"
#include "Avatar.h"
#include "Kismet/GameplayStatics.h"
#include "Bullet.h"
#include "Engine/SkeletalMeshSocket.h"
#include "MonsterAIController.h"

// Sets default values
AMonster::AMonster(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Speed = 20;
	HitPoints = 20;
	Experience = 0;
	BPLoot = NULL;
	BaseAttackDamage = 1;
	AttackTimeout = 1.5f;
	TimeSinceLastStrike = 0;

	SightSphere = ObjectInitializer.CreateDefaultSubobject<USphereComponent>
		(this, TEXT("SightSphere"));
	SightSphere->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);

	AttackRangeSphere = ObjectInitializer.CreateDefaultSubobject
		<USphereComponent>(this, TEXT("AttackRangeSphere"));
	AttackRangeSphere->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
}

// Called every frame
void AMonster::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// move the monster towards the player 
	AAvatar *avatar = Cast<AAvatar>(
		UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (!avatar) return;

	FVector playerPos = avatar->GetActorLocation();
	FVector toPlayer = playerPos - GetActorLocation();
	float distanceToPlayer = toPlayer.Size();
	AMonsterAIController* controller = Cast<AMonsterAIController>(GetController());

	// If the player is not the SightSphere of the monster, 
	// go back 
	if (distanceToPlayer > SightSphere->GetScaledSphereRadius())
	{
		// If the player is OS, then the enemy cannot chase 
		if (controller != nullptr)
		{
			controller->SetAttackRange(false);
			controller->SetFollowRange(false);
		}
		return;
	}

	toPlayer /= distanceToPlayer;  // normalizes the vector 

								   // At least face the target 
								   // Gets you the rotator to turn something 
								   // that looks in the `toPlayer` direction 
	FRotator toPlayerRotation = toPlayer.Rotation();
	toPlayerRotation.Pitch = 0; // 0 off the pitch 
	RootComponent->SetWorldRotation(toPlayerRotation);


	if (isInAttackRange(distanceToPlayer))
	{
		if (controller != nullptr)
		{
			controller->SetAttackRange(true);
		}

		// Perform the attack 
		if (!TimeSinceLastStrike)
		{
			Attack(avatar);
		}

		TimeSinceLastStrike += DeltaSeconds;
		if (TimeSinceLastStrike > AttackTimeout)
		{
			TimeSinceLastStrike = 0;
		}

		return;  // nothing else to do 
	}
	else
	{
		// not in attack range, so walk towards player 
		//AddMovementInput(toPlayer, Speed*DeltaSeconds);

		if (controller != nullptr)
		{
			controller->SetAttackRange(false);
			controller->SetFollowRange(true);
		}
	}
}

void AMonster::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	// instantiate the melee weapon if a bp was selected 
	if (BPMeleeWeapon)
	{
		MeleeWeapon = GetWorld()->SpawnActor<AMeleeWeapon>(
			BPMeleeWeapon, FVector(), FRotator());

		if (MeleeWeapon)
		{
			const USkeletalMeshSocket *socket = GetMesh()->GetSocketByName(
				FName("RightHandSocket")); // be sure to use correct 
									// socket name! 
			socket->AttachActor(MeleeWeapon, GetMesh());
			MeleeWeapon->WeaponHolder = this;
		}
	}
}

void AMonster::SwordSwung()
{
	if (MeleeWeapon)
	{
		MeleeWeapon->Swing();
	}
}

void AMonster::Attack(AActor* thing)
{
	if (MeleeWeapon)
	{
		// code for the melee weapon swing, if  
		// a melee weapon is used 
		MeleeWeapon->Swing();
	}
	else if (BPBullet)
	{
		// If a blueprint for a bullet to use was assigned, 
		// then use that. Note we wouldn't execute this code 
		// bullet firing code if a MeleeWeapon was equipped 
		FVector fwd = GetActorForwardVector();
		FVector nozzle = GetMesh()->GetBoneLocation("RightHand");
		nozzle += fwd * 155;// move it fwd of the monster so it doesn't 
			// collide with the monster model 
			FVector toOpponent = thing->GetActorLocation() - nozzle;
		toOpponent.Normalize();
		ABullet *bullet = GetWorld()->SpawnActor<ABullet>(
			BPBullet, nozzle, RootComponent->GetComponentRotation());

		if (bullet)
		{
			bullet->Firer = this;
			bullet->ProxSphere->AddImpulse(
				toOpponent*BulletLaunchImpulse);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(0, 5.f,
				FColor::Yellow, "monster: no bullet actor could be spawned. is the bullet overlapping something ? " ); 
		}
	}
}