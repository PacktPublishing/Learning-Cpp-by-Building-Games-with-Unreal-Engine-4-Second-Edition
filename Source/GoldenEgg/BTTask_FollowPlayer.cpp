// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_FollowPlayer.h"
#include "MonsterAIController.h"


EBTNodeResult::Type UBTTask_FollowPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AMonsterAIController* Controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());
	if (Controller == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	Controller->StartFollowingPlayer();

	return EBTNodeResult::Succeeded;
}