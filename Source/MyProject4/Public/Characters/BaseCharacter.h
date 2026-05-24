
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/HitInterface.h"
#include "Characters/CharacterTypes.h"
#include "BaseCharacter.generated.h"

class AWeapon;
class UAttributeComponent;
class UAnimMontage;

UCLASS()
class MYPROJECT4_API ABaseCharacter : public ACharacter, public IHitInterface
{
	GENERATED_BODY()

public:
	
	ABaseCharacter();
    virtual void Tick(float DeltaTime) override;
	FORCEINLINE TEnumAsByte <EDeathPose> GetDeathPose() const { return DeathPose; }
	
protected:

	virtual void BeginPlay() override;
	virtual void GetHit_Implementation(const FVector& ImpactPoint,AActor* Hitter)override;
	virtual void Attack();
	virtual void Die();
    void DirectionalHitReact(const FVector& ImpactPoint);
    void PlayHitSound(const FVector& ImpactPoint);
	void SpawnHitParticles(const FVector& ImpactPoint);
	virtual void HandleDamage(float DamageAmount);
    void DisableCapsule();
    virtual bool CanAttack();
	bool IsAlive();
	void DisableMeshCollision();

	UFUNCTION(BlueprintCallable)
	virtual void AttackEnd();

	UFUNCTION(BlueprintCallable)
	virtual void DodgeEnd();

	UFUNCTION(BlueprintCallable)
	void SetWeaponCollisionEnabled(ECollisionEnabled::Type CollisionEnabled);
	
	/*
	Play montage function
	*/

	virtual int32 PlayAttackMontage();
	void  PlayHitReactMontage(const FName& SectionName);
	virtual int32 PlayDeathMontage();
	virtual void PlayDodgeMontage();
	void StopAttackMontage();

	UFUNCTION(BlueprintCallable)
	FVector GetTranslationWarpTarget();

	UFUNCTION(BlueprintCallable)
	FVector GetRotationWarpTarget();

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	AWeapon* EquippedWeapon;

	UPROPERTY(BlueprintReadOnly, Category = Combat)
	AActor* CombatTarget;

	UPROPERTY(EditAnywhere, Category= Combat)
	double WarpTargetDistance = 75.f;
	/*
	* Components
	*/

	UPROPERTY(VisibleAnywhere)
	UAttributeComponent* Attributes;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TEnumAsByte<EDeathPose> DeathPose;

private:
	void PlayMontageSection(UAnimMontage* Montage, const FName& SectionName);
	int32 PlayRandomMontageSection(UAnimMontage* Montage, const TArray<FName>& SectionNames);

	UPROPERTY(EditAnywhere, Category = Combat)
	USoundBase* HitSound;

	UPROPERTY(EditAnywhere, Category = Combat)
	UParticleSystem* HitParticles;

	/*
    // Animation Montages
    */
	UPROPERTY(EditDefaultsOnly, Category = Combat)
	UAnimMontage* AttackMontage;

	UPROPERTY(EditDefaultsOnly, Category = Combat)
	UAnimMontage* HitReactMontage;

	UPROPERTY(EditDefaultsOnly, Category = Combat)
	UAnimMontage* DeathMontage;

	UPROPERTY(EditDefaultsOnly, Category = Combat)
	UAnimMontage* DodgeMontage;

	UPROPERTY(EditAnywhere,Category= Combat)
	TArray <FName> AttackMontageSections;

	UPROPERTY(EditAnywhere, Category = Combat)
	TArray <FName> DeathMontageSections;
};
