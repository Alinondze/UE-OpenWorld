
#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "CharacterTypes.h"
#include "Interfaces/PickUpInterface.h"
#include "SlashCharacter.generated.h"

class  USpringArmComponent;
class UCameraComponent;
class UGroomComponent;
class AItem;
class ASoul;
class UAnimMontage;
class USlashOverlay;

UCLASS()
class MYPROJECT4_API ASlashCharacter : public ABaseCharacter,public IPickUpInterface
{
	GENERATED_BODY()

public:
	
	ASlashCharacter();
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigatir, AActor* DamageCause)override;
	virtual void Jump()override;
	virtual void SetOverlappingItem( AItem* Item)override;
	virtual void AddSouls(ASoul* Soul)override;
protected:
	
	virtual void BeginPlay() override;

	

	/* Callbacks for input */
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);
	void EKeyPressed();
	virtual void Attack() override;


	

public:
	virtual void GetHit_Implementation(const FVector& ImpactPoint, AActor* Hitter) override;
    /* Combat */
	void EquipWeapon(AWeapon* Weapon);
	virtual void AttackEnd() override;
	virtual bool CanAttack() override;
	void PlayEquipMontage(const FName& SectionName);
	bool CanDisarm();
	bool CanArm();
	void Disarm();
	void Arm();
	virtual void Die()override;
	UFUNCTION(BlueprintCallable)
	void AttachWeaponToBack();

	UFUNCTION(BlueprintCallable)
	void AttachWeaponToHand();

	UFUNCTION(BlueprintCallable)
	void FinishEquipping();

	UFUNCTION(BlueprintCallable)
	void HitReactEnd();

private:
	bool IsUnoccupied();
	void InitializeSlashOverlay();
	void SetHUDHealth();

	/* Character components */
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* ViewCamera;

	UPROPERTY(VisibleAnywhere , Category=Hair)
	UGroomComponent* Hair;

	UPROPERTY(VisibleAnywhere, Category = Hair)
	UGroomComponent* Eyebrows;

	UPROPERTY(VisibleInstanceOnly)
	AItem* OverlappingItem;

	UPROPERTY(EditDefaultsOnly, Category = Montages)
	UAnimMontage* EquipMontage;

	ECharacterState CharacterState = ECharacterState::ECS_Unequipped;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EActionState ActionState = EActionState::EAS_Unoccupied;

	UPROPERTY()
	USlashOverlay* SlashOverlay;

public:	
	
	FORCEINLINE ECharacterState GetCharacterState() const { return CharacterState; }
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	FORCEINLINE EActionState GetActionState() const { return ActionState; }
	

	
};
