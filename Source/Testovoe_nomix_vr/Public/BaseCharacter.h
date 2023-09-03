// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseTicket.h"
#include "TicketInventory.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class TESTOVOE_NOMIX_VR_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	// Ссылка на инвентарь билетов
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory")
	ATicketInventory* TicketInventory;

	// Текущий используемый объект
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Interaction")
	AActor* FocusedActor;

	UPROPERTY()
	ABaseTicket* ActiveTicket;

	UFUNCTION()
	void OnOverlapTicket(ABaseTicket* OverlappedTicket);

	UFUNCTION()
	void TakeTicket();

	UFUNCTION()
	void UseTicket();

	UFUNCTION()
	void FocusOnActor(AActor* Actor);

	UFUNCTION()
	void InteractWithActor();
	UFUNCTION()
	void StopInteractWithActor();

	UFUNCTION()
	void ValveRotator(float Value);	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(const float Value);
	void LookUp(const float Value);

	void PrevTicket();
	void NextTicket();

	

	FVector Velocity;
	float MoveSpeed = 100.f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
