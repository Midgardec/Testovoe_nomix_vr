// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UInteractiveInterface.h"
#include "GameFramework/Actor.h"
#include "BaseTicket.generated.h"

UCLASS()
class TESTOVOE_NOMIX_VR_API ABaseTicket : public AActor, public IUInteractiveInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseTicket();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ticket")
	int32 TicketNumber;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ticket")
	FDateTime DateIssued;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ticket")
	int32 TurnstileIdNumber;
	
	void SetTicketNumber(int32 value);
	void SetTurnstileIdNumber(int32 value);
public:	

	
	UFUNCTION(BlueprintCallable)
	bool IsValid();

	UFUNCTION(BlueprintCallable)
	void GetTicketInfo(int32& OutNumber, FDateTime& OutDate);

	UFUNCTION(BlueprintCallable)
	virtual int32 GetTurnstileId();

	UFUNCTION(BlueprintCallable)
	virtual void OnUsed() override;

	UFUNCTION(BlueprintCallable)
	virtual void OnEndUsed() override;
};
