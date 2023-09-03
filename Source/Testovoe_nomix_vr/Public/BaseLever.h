// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UInteractiveInterface.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "BaseLever.generated.h"

UCLASS()
class TESTOVOE_NOMIX_VR_API ABaseLever : public AActor, public IUInteractiveInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseLever();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMeshComponent* Mesh;

	bool bAnimateRotation = false;

	float DefaultRotationAngle= 0;
	float DesiredRotationAngle =  100.f;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	virtual void OnUsed() override;

	UFUNCTION(BlueprintCallable)
	virtual void OnEndUsed() override;
	
	UFUNCTION(BlueprintCallable)
	void AnimateOpen();
	
	UFUNCTION(BlueprintCallable)
	void AnimateClose();

};
