// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyController.h"

#include "Enemy.h"


void AEnemyController::MakeAttackDecision(AActor* TargetPawn)
{
	AEnemy* EnemyCharacter = Cast<AEnemy>(GetPawn());
	if (!EnemyCharacter) return;
	
	double Dist = FVector::Dist2D(TargetPawn->GetActorLocation(), GetPawn()->GetActorLocation());
	if (Dist <= EnemyCharacter->AttackRange && EnemyCharacter->CanAttack()) 
		EnemyCharacter->Attack();
}

