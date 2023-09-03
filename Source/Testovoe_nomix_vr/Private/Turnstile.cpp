// Fill out your copyright notice in the Description page of Project Settings.


#include "Turnstile.h"
#include "BaseTicket.h"
#include <Kismet/KismetMathLibrary.h>

// Sets default values
ATurnstile::ATurnstile()
{
	PrimaryActorTick.bCanEverTick = true;

	bIsOpen = false;
	bIsLocked = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
}

// Called when the game starts or when spawned
void ATurnstile::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATurnstile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bAnimateOpenDoors) {
		AnimateOpenDoors();
		timer_ += DeltaTime;
	}
	else {
		AnimateCloseDoors();
	}
	if(timer_ > 5.0f){
		bAnimateOpenDoors = false;
		
		timer_ = 0;
	}
}

void ATurnstile::Activate(ABaseTicket* Ticket)
{
	// Check ticket 

	if (Ticket->IsValid() && Ticket->GetTurnstileId() == this->TurnstileId)
	{
		if (!bIsLocked)
		{
			// Open turnstile
			bIsOpen = true;
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Green, FString::Printf(TEXT("opened door %i"), TurnstileId));
			bAnimateOpenDoors = true;
			return;
		}
	}
	
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Green, FString::Printf(TEXT("ticket is not valid for door %i"), TurnstileId));

}
int32 ATurnstile::GetTurnstileId()
{
	return TurnstileId;
}
void ATurnstile::GetTurnstileState(bool& OutIsOpen, bool& OutIsLocked)
{
	OutIsOpen = bIsOpen;
	OutIsLocked = bIsLocked;
}

void ATurnstile::AnimateOpenDoors()
{

	FRotator CurrentRotation = Mesh->GetComponentRotation();

	FRotator NewRotation = FRotator(70.f,0,0);

	FRotator TargetRotation = UKismetMathLibrary::RInterpTo(CurrentRotation, NewRotation, GetWorld()->GetDeltaSeconds(),2.0f);
	
	Mesh->SetRelativeRotation(TargetRotation);

}

void ATurnstile::AnimateCloseDoors()
{
	FRotator CurrentRotation = Mesh->GetComponentRotation();

	
	FRotator NewRotation = FRotator(0, 0, 0);

	FRotator TargetRotation = UKismetMathLibrary::RInterpTo(CurrentRotation, NewRotation, GetWorld()->GetDeltaSeconds(), 2.0f);

	Mesh->SetRelativeRotation(TargetRotation);
	
	bIsOpen = false;
}