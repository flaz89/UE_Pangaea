// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance/PlayerAvatarAnimInstance.h"

#include "Actors/PlayerAvatar.h"


void UPlayerAvatarAnimInstance::OnStateAnimationEnds()
{
	// if the current state is "attack" set the state to "locomotion"
	if (PlayerState == EPlayerState::Attack)
	{
		PlayerState = EPlayerState::Locomotion;
	}
	else
	{
		// if not extract the playeravatar class reference
		AActor* AnimInstanceOwner = GetOwningActor();
		APlayerAvatar* PlayerAvatar = Cast<APlayerAvatar>(AnimInstanceOwner);
		if (PlayerAvatar == nullptr) return;
		
		// check the current state is "hit", if so check the healt points, 
		// if they are greater than 0 set the state to "locomotion" otherwise set to "die"
		if (PlayerState == EPlayerState::Hit)
		{
			if (PlayerAvatar->GetHealthPoints() > 0)
			{
				PlayerState = EPlayerState::Locomotion;
			}
			else
			{
				PlayerState = EPlayerState::Die;
			}
		}
		else if (PlayerState == EPlayerState::Die)
		{
			//.. die process
		}
	}
}
