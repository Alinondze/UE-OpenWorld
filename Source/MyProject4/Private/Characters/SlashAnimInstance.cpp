//// Fill out your copyright notice in the Description page of Project Settings.
//#include "Characters/SlashAnimInstance.h"
//#include "Character/SlashCharacter.h"
//#include "GameFramework/CharacterMovementComponent.h"
//#include "Kismet/KismetMathlibrary.h"
//
//void USlashAnimInstance::NativeinitializeAnimation()
//{
//	Super::NativeInitializeAnimation();
//
//	SlashCharacter = Cast<ASlashCharacter>(TryGetPawnOwner());
//	if (SlashCharacter)
//	{
//		SlashCharacterMovement= SlashCharacter->GetCharacterMovement();
//	}
//	
//}
//
//void USlashAnimInstance::NativeUpdateAnimation(float DeltaTime)
//{
//	Super::NativeUpdateAnimation(DeltaTime);
//	if (SlashCharacterMovement)
//	{
//		
//		GroundSpeed= UKismetMathLibrary::VSizeXY(SlashCharacterMovement->Velocity);
//	}
//}
