// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UTurnstileInterface.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Turnstile.generated.h"

UCLASS()
class TESTOVOE_NOMIX_VR_API ATurnstile : public AActor, public IUTurnstileInterface
{
	GENERATED_BODY()

	
public:	
	// Sets default values for this actor's properties
	ATurnstile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	int32 TurnstileId;

	UPROPERTY(VisibleAnywhere)
	bool bIsOpen;

	UPROPERTY(VisibleAnywhere)
	bool bIsLocked;

	UPROPERTY()
	bool bAnimateOpenDoors = false;

	float timer_ = 0;
public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	virtual void Activate(class ABaseTicket* Ticket) override;
	
	virtual int32 GetTurnstileId();
	UFUNCTION(BlueprintCallable)
	virtual void GetTurnstileState(bool& OutIsOpen, bool& OutIsLocked) ;
	UFUNCTION(BlueprintCallable)
	virtual bool IsOpen() { return bIsOpen; }

	UFUNCTION(BlueprintCallable)
	void AnimateOpenDoors();

	UFUNCTION(BlueprintCallable)
	void AnimateCloseDoors();
};
