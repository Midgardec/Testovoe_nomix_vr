// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseTicket.h"

// Sets default values
ABaseTicket::ABaseTicket()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseTicket::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseTicket::SetTicketNumber(int32 value)
{
	TicketNumber = value;
}

void ABaseTicket::SetTurnstileIdNumber(int32 value)
{
	TurnstileIdNumber = value;
}

bool ABaseTicket::IsValid()
{
	// Проверка валидности билета

	return true;
}

void ABaseTicket::GetTicketInfo(int32& OutNumber, FDateTime& OutDate)
{
	OutNumber = TicketNumber;
	OutDate = DateIssued;
}

int32 ABaseTicket::GetTurnstileId()
{
	return TurnstileIdNumber;
}

void ABaseTicket::OnUsed()
{
	return;
}

void ABaseTicket::OnEndUsed()
{
	return;
}
