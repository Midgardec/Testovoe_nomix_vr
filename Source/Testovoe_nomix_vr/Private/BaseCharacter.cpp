// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "UInteractiveInterface.h"
#include "UTurnstileInterface.h"
#include "Turnstile.h"
#include <BaseValve.h>
// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ActiveTicket = nullptr;
	FocusedActor = nullptr;
	TicketInventory = CreateDefaultSubobject<ATicketInventory>(TEXT("Ticket_Inventory"));



}

void ABaseCharacter::OnOverlapTicket(ABaseTicket* OverlappedTicket)
{
	
	if (!TicketInventory) {
		return;
	}
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Cyan, FString::Printf(TEXT("took ticket %i"),OverlappedTicket->GetTurnstileId()));
	
	TicketInventory->AddTicket(OverlappedTicket);
	TicketInventory->SetActiveTicket(OverlappedTicket);
	ActiveTicket = OverlappedTicket;	
}

void ABaseCharacter::TakeTicket()
{
	// Взять активный билет в руку
	if (!TicketInventory) {
		return;
	}
	ActiveTicket = TicketInventory->GetActiveTicket();
}

void ABaseCharacter::UseTicket()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Magenta, FString::Printf(TEXT("Use")));

	
	if (!FocusedActor) {
		return;
	}

	TakeTicket();

	if (!ActiveTicket) {
		return;
	}

	

	IUTurnstileInterface* Turnstile = Cast<IUTurnstileInterface>(FocusedActor);

	if (Turnstile)
	{
		// Использовать билет на турникете
		Turnstile->Activate(ActiveTicket);
	}
}

void ABaseCharacter::FocusOnActor(AActor* Actor)
{
	FocusedActor = Actor;
}

void ABaseCharacter::InteractWithActor()
{
	if (!FocusedActor) {
		return;
	}

	IUInteractiveInterface* Interactive = Cast<IUInteractiveInterface>(FocusedActor);

	if (Interactive)

	{
		// Использовать интерфейс
		Interactive->OnUsed();
		//Interactive->OnEndUsed();
	}
	
	if (ABaseTicket* Ticket_ = Cast<ABaseTicket>(FocusedActor)) {
		OnOverlapTicket(Ticket_);
	}
	
	
}

void ABaseCharacter::StopInteractWithActor() {
	if (!FocusedActor) {
		return;
	}
	IUInteractiveInterface* Interactive = Cast<IUInteractiveInterface>(FocusedActor);
	if (Interactive)

	{
		// Использовать интерфейс
		//Interactive->OnUsed();
		Interactive->OnEndUsed();
	}
}

void ABaseCharacter::ValveRotator(float Value)
{
	if (Value == 0) {
		return;
	}
	if (!FocusedActor) {
		return;
	}
	//ABaseValve* Valve = Cast<ABaseValve>(FocusedActor);
	if (ABaseValve* Valve = Cast<ABaseValve>(FocusedActor))

	{
		// Использовать интерфейс
		//Interactive->OnUsed();
		Valve->Rotate(Value*10);
	}
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	FActorSpawnParameters SpawnParametrs = FActorSpawnParameters();

	if (GetWorld()) {
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Magenta, FString::Printf(TEXT("ADDED ticket0 to inventory for test")));
		TicketInventory = GetWorld()->SpawnActor<ATicketInventory>(ATicketInventory::StaticClass(), SpawnParametrs);
	}

}

void ABaseCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// Find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// Get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction , Value);
	}
}

void ABaseCharacter::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// Find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// Get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// Add movement in that direction
		AddMovementInput(Direction , Value);
	}
}

void ABaseCharacter::Turn(const float Value)
{
	AddControllerYawInput(Value);
}

void ABaseCharacter::LookUp(const float Value)
{
	AddControllerPitchInput(Value);
}
void ABaseCharacter::PrevTicket()
{
	TicketInventory->PreviousTicket();
}
void ABaseCharacter::NextTicket()
{
	TicketInventory->NextTicket();
}
// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ABaseCharacter::InteractWithActor);
	PlayerInputComponent->BindAction("Interact", IE_Released, this, &ABaseCharacter::StopInteractWithActor);

	PlayerInputComponent->BindAxis("Scroller", this, &ABaseCharacter::ValveRotator);

	PlayerInputComponent->BindAction("UseTicket", IE_Pressed, this, &ABaseCharacter::UseTicket);
	PlayerInputComponent->BindAction("Prev", IE_Pressed, this, &ABaseCharacter::PrevTicket);
	PlayerInputComponent->BindAction("Next", IE_Pressed, this, &ABaseCharacter::NextTicket);

	PlayerInputComponent->BindAxis("MoveForward", this, &ABaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABaseCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &ABaseCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &ABaseCharacter::LookUp);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

}

