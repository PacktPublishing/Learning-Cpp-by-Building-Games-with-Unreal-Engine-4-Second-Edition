// Fill out your copyright notice in the Description page of Project Settings.

#include "MonsterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "Monster.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

AMonsterAIController::AMonsterAIController(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	BehaviorTreeCmp = ObjectInitializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("MonsterBT"));
	BlackboardCmp = ObjectInitializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("MonsterBlackboard"));
}

void AMonsterAIController::Possess(class APawn* InPawn)
{
	Super::Possess(InPawn);

	AMonster* Monster = Cast<AMonster>(InPawn);
	if (Monster)
	{
		if (Monster->BehaviorTree->BlackboardAsset)
		{
			BlackboardCmp->InitializeBlackboard(*Monster->BehaviorTree->BlackboardAsset);
		}

		BehaviorTreeCmp->StartTree(*Monster->BehaviorTree);
	}
}


void AMonsterAIController::UnPossess()
{
	Super::UnPossess();

	BehaviorTreeCmp->StopTree();
}

void AMonsterAIController::SetFollowRange(bool val)
{
	BlackboardCmp->SetValueAsBool("IsInFollowRange", val);
}

void AMonsterAIController::SetAttackRange(bool val)
{
	BlackboardCmp->SetValueAsBool("IsInAttackRange", val);
}

void AMonsterAIController::StartFollowingPlayer()
{
	AActor *player = Cast<AActor>(
		UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	FVector playerPos = player->GetActorLocation();
	MoveToLocation(playerPos);
}