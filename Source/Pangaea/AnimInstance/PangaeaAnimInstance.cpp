// Fill out your copyright notice in the Description page of Project Settings.


#include "PangaeaAnimInstance.h"
#include "Actors/PangaeaBaseCharacter.h"


void UPangaeaAnimInstance::OnStateAnimationEnds()
{
	if (State == ECharacterState::Attack)
	{
		State = ECharacterState::Locomotion;
	} 
	else
	{
		APangaeaBaseCharacter* Character = Cast<APangaeaBaseCharacter>(GetOwningActor());
		if (State == ECharacterState::Hit)
		{
			if (Character->GetHealthPoints() > 0.f)
			{
				State = ECharacterState::Locomotion;
			}
			else
			{
				State = ECharacterState::Die;
			}
		}
		else if (State == ECharacterState::Die)
		{
			Character->DieProcess();
		}
	}
	
}
