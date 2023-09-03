// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseLever.h"
#include <Kismet/KismetMathLibrary.h>

// Sets default values
ABaseLever::ABaseLever()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
}

// Called when the game starts or when spawned
void ABaseLever::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseLever::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bAnimateRotation) {
		AnimateOpen();
	}
	else {
		AnimateClose();
	}

}

void ABaseLever::OnUsed()
{
	bAnimateRotation = true;

}

void ABaseLever::OnEndUsed()
{
	bAnimateRotation = false;

}

void ABaseLever::AnimateOpen() {

	FRotator CurrentRotation = Mesh->GetComponentRotation();

	FRotator NewRotation = FRotator(CurrentRotation.Pitch, CurrentRotation.Yaw, DesiredRotationAngle) ;

	FRotator TargetRotation = UKismetMathLibrary::RInterpTo(CurrentRotation, NewRotation, GetWorld()->GetDeltaSeconds(), 2.0f);

	Mesh->SetRelativeRotation(TargetRotation);
}
void ABaseLever::AnimateClose() {

	FRotator CurrentRotation = Mesh->GetComponentRotation();

	FRotator NewRotation = FRotator(CurrentRotation.Pitch, CurrentRotation.Yaw, DefaultRotationAngle) ;

	FRotator TargetRotation = UKismetMathLibrary::RInterpTo(CurrentRotation, NewRotation, GetWorld()->GetDeltaSeconds(), 2.0f);
 
	Mesh->SetRelativeRotation(TargetRotation);
}