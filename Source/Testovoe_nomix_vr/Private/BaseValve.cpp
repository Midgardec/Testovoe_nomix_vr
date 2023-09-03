#include "BaseValve.h"
// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseValve.h"
#include <Kismet/KismetMathLibrary.h>

// Sets default values
ABaseValve::ABaseValve()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
}

// Called when the game starts or when spawned
void ABaseValve::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseValve::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AnimateRoll(AnimRollAngle);

	/*if (!bManualRotation) {
		if (bAnimateRotation) {
			AnimateRoll(DesiredRoll);
		}
		else {
			AnimateRoll(DefaultRoll);
		}
	}
	else {
		AnimateRoll(ManualRoll);
	}*/
	
}

void ABaseValve::OnUsed()
{
	bManualRotation = false;
	bAnimateRotation = true;
	AnimRollAngle = DesiredRoll;
}

void ABaseValve::OnEndUsed()
{
	bAnimateRotation = false;
	AnimRollAngle = DefaultRoll;
}

void ABaseValve::AnimateRoll(float value) {
	
	FRotator CurrentRotation = Mesh->GetComponentRotation();

	FRotator NewRotation = FRotator(CurrentRotation.Pitch, CurrentRotation.Yaw, FMath::Clamp(value, minRoll, maxRoll));

	FRotator TargetRotation = UKismetMathLibrary::RInterpTo(CurrentRotation, NewRotation, GetWorld()->GetDeltaSeconds(), 2.0f);
	
	Mesh->SetRelativeRotation(TargetRotation);
	
}


void ABaseValve::Rotate(float Value)
{
	bManualRotation = true;
	ManualRoll =  FMath::Clamp(AnimRollAngle + Value, minRoll, maxRoll);
	AnimRollAngle = ManualRoll;
}
