

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Bird.generated.h"


class UCapsuleComponent;
class USkeletalMeshComponent;
class  USpringArmComponent;
class UCameraComponent;
class UFloatingPawnMovement;

UCLASS()
class MYPROJECT4_API ABird : public APawn
{
	GENERATED_BODY()

public:
	
	ABird();

virtual void Tick(float DeltaTime) override;

virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
protected:
	
	virtual void BeginPlay() override;
	void MoveForward(float Value);
	void Turn(float Value);
	void LookUp(float Value);

	
	
	protected: 

	UPROPERTY(VisibleAnywhere)
	 UCapsuleComponent* Capsule;

	 UPROPERTY(VisibleAnywhere)
	 USkeletalMeshComponent* BirdMesh;

	 UPROPERTY(VisibleAnywhere)
	 USpringArmComponent* SpringArm;

	 UPROPERTY(VisibleAnywhere)
	 UCameraComponent* ViewCamera;

	 UPROPERTY(VisibleAnywhere)
	 UFloatingPawnMovement* MovementComponent;
};
