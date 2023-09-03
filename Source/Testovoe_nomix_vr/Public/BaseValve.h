// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UInteractiveInterface.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "BaseValve.generated.h"

UCLASS()
class TESTOVOE_NOMIX_VR_API ABaseValve : public AActor, public IUInteractiveInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseValve();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMeshComponent* Mesh;

	bool bAnimateRotation =false;
	bool bManualRotation = true;
	float DefaultRoll = 0;
	float DesiredRoll = -170.f;
	float maxRoll = 170.f;
	float minRoll = -170.f;
	float ManualRoll = 0;

	float AnimRollAngle = 0;
	bool bDirection = 1;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	virtual void OnUsed() override;

	UFUNCTION(BlueprintCallable)
	virtual void OnEndUsed() override;
	
	UFUNCTION(BlueprintCallable)
	void AnimateRoll(float Value);

	/*UFUNCTION(BlueprintCallable)
	void AnimateClose();*/

	UFUNCTION()
	void Rotate(float Value);
};
