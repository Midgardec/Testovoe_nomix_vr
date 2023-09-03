// Fill out your copyright notice in the Description page of Project Settings.


#include "TicketInventory.h"

// Sets default values
ATicketInventory::ATicketInventory()
{


}

// Called when the game starts or when spawned
void ATicketInventory::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATicketInventory::AddTicket(ABaseTicket* Ticket)
{
	int32 number = -1; 
	FDateTime outdate_;
	if (Ticket)
	{
		Ticket->GetTicketInfo(number, outdate_);
		Inventory.Add(number, Ticket);
	}
}

ABaseTicket* ATicketInventory::GetActiveTicket()
{
	return ActiveTicket;
}

void ATicketInventory::SetActiveTicket(ABaseTicket* Ticket)
{
	if (Inventory.FindKey(Ticket)) {
		ActiveTicket = Ticket;
	}
	
}

void ATicketInventory::GetInventoryItems(TArray<ABaseTicket*>& InventoryItems)
{
	Inventory.GenerateValueArray(InventoryItems);
}

void ATicketInventory::PreviousTicket()
{
	TArray<int32> Keys;
	Inventory.GetKeys(Keys);

	int32 SelectedKey;
	SelectedKey = *Inventory.FindKey(ActiveTicket);

	int32 NewIndex = Keys.IndexOfByKey(SelectedKey) - 1;
	if (NewIndex < 0)
	{
		NewIndex = Keys.Num() - 1;
	}
	SelectedKey = Keys[NewIndex];

	ABaseTicket** FoundTicketPtr = Inventory.Find(SelectedKey);

	if (FoundTicketPtr)
	{
		ABaseTicket* FoundTicket = *FoundTicketPtr;

		ActiveTicket = FoundTicket;
	}
}

void ATicketInventory::NextTicket()
{
	TArray<int32> Keys;
	Inventory.GetKeys(Keys);

	int32 SelectedKey;
	SelectedKey = *Inventory.FindKey(ActiveTicket);

	int32 NewIndex = Keys.IndexOfByKey(SelectedKey) + 1;
	if (NewIndex >= Inventory.Num())
	{
		NewIndex = 0;
	}
	SelectedKey = Keys[NewIndex];


	ABaseTicket** FoundTicketPtr = Inventory.Find(SelectedKey);

	if (FoundTicketPtr)
	{
		ABaseTicket* FoundTicket = *FoundTicketPtr;

		ActiveTicket = FoundTicket;
	}


	/*ABaseTicket* FoundTicket = Inventory.FindRef(SelectedKey);

	if (FoundTicket)
	{
		ActiveTicket = FoundTicket;
	}*/
	//ActiveTicket = Inventory[NewIndex];
}
