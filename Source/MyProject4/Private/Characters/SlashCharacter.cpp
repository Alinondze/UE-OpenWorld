
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Characters/SlashCharacter.h"


ASlashCharacter::ASlashCharacter()
{

	PrimaryActorTick.bCanEverTick = true;

	

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 300.f;

	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
	ViewCamera->SetupAttachment(SpringArm);
}


void ASlashCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}


void ASlashCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ASlashCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(FName("MoveForward"), this, &ASlashCharacter::MoveForward);
	PlayerInputComponent->BindAxis(FName("Turn"), this, &ASlashCharacter::Turn);
	PlayerInputComponent->BindAxis(FName("LookUp"), this, &ASlashCharacter::LookUp);
	PlayerInputComponent->BindAxis(FName("MoveRight"), this, &ASlashCharacter::MoveRight);

}

 void ASlashCharacter::MoveForward(float Value)
{
	 if (Controller != nullptr && (Value != 0))
	 {
		 FVector Forward = GetActorForwardVector();
		 AddMovementInput(Forward, Value);
     }

}

 void ASlashCharacter::MoveRight(float Value)
 {
	 if (Controller != nullptr && (Value != 0))
	 {
		 FVector Right = GetActorForwardVector();
		 AddMovementInput(Right, Value);
	 }
 }

 void ASlashCharacter::Turn(float Value)
 {
	 AddControllerYawInput(Value);

 }

 void ASlashCharacter::LookUp(float Value)
 {
	 AddControllerPitchInput(Value);

 }

