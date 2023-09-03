// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseTicket.h"
#include "GameFramework/Actor.h"
#include "TicketInventory.generated.h"


UCLASS()
class TESTOVOE_NOMIX_VR_API ATicketInventory : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATicketInventory();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere)
	TMap<int32, ABaseTicket*> Inventory;

	UPROPERTY()
	ABaseTicket* ActiveTicket;
public:	

	void AddTicket(ABaseTicket* Ticket);

	UFUNCTION(BlueprintCallable)
	ABaseTicket* GetActiveTicket();

	void SetActiveTicket(ABaseTicket* Ticket);

	UFUNCTION(BlueprintCallable)
	void GetInventoryItems(TArray<ABaseTicket*>& InventoryItems);

	UFUNCTION()
	void PreviousTicket();

	UFUNCTION()
	void NextTicket();

};
