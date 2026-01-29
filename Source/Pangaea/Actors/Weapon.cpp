// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

#include "PlayerAvatar.h"


// Sets default values
AWeapon::AWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	RootComponent = MeshComponent;
}

void AWeapon::OnWeaponBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	APlayerAvatar* PlayerAvatar = Cast<APlayerAvatar>(OtherActor);
	if (PlayerAvatar == nullptr) return;
	if (Holder == nullptr)
	{
		Holder = PlayerAvatar;
		
		TArray<AActor*> AttachedActors;
		OtherActor->GetAttachedActors(AttachedActors, true);
		for (int i = 0 ; i < AttachedActors.Num(); ++i)
		{
			AttachedActors[i]->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
			AttachedActors[i]->SetActorRotation(FQuat::Identity);
			if (AWeapon* Weapon = Cast<AWeapon>(AttachedActors[i])) Weapon->Holder = nullptr;
		}
		AttachToComponent(Holder->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("hand_rSocket"));
	}
	else if (IsWithinAttackRange(0.f, OtherActor))
	{
		//............................
	}
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	OnActorBeginOverlap.AddDynamic(this, &AWeapon::OnWeaponBeginOverlap);
}

bool AWeapon::IsWithinAttackRange(float AttackRange, AActor* Target)
{
	return false;
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (Holder == nullptr)
	{
		FQuat RotationQuat = FQuat(FRotator(0.f, 300.f * DeltaTime, 0.f));
		AddActorLocalRotation(RotationQuat);
	}
}

