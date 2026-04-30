

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/HitInterface.h"
#include "Characters/CharacterTypes.h"
#include "Enemy.generated.h"


class UAnimMontage;
class UAttributeComponent;
class UHealthBarComponent;
class AAIController;
class UPawnSensingComponent;

UCLASS()
class MYPROJECT4_API AEnemy : public ACharacter, public IHitInterface
{
	GENERATED_BODY()

public:
	
	AEnemy();

    virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void GetHit_Implementation(const FVector& ImpactPoint) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigatir, AActor* DamageCause)override;
	
private:
	/*
	* Components
	*/

	UPROPERTY(VisibleAnywhere)
	UAttributeComponent* Attributes;

	UPROPERTY(VisibleAnywhere)
	UHealthBarComponent* HealthBarWidget;

	UPROPERTY(VisibleAnywhere)
	UPawnSensingComponent* PawnSensing;
	/*
	// Animation Montages
	*/
	UPROPERTY(EditDefaultsOnly, Category = Montages)
	UAnimMontage* HitReactMontage;

	UPROPERTY(EditDefaultsOnly, Category = Montages)
	UAnimMontage* DeathMontage;

	UPROPERTY(EditAnywhere, Category= Sounds)
	USoundBase* HitSound;

	UPROPERTY(EditAnywhere, Category = VisualEffects)
	UParticleSystem* HitParticles;

	UPROPERTY()
	AActor* CombatTarget;

	UPROPERTY(EditAnywhere)
	double  CombatRadius = 500.f;

	UPROPERTY(EditAnywhere)
	double  AttackRadius = 150.f;

	/*
	* Navigation
	*/
	UPROPERTY()
	AAIController* EnemyController;

	UPROPERTY(EditInstanceOnly,Category = "AI Navigation")
	AActor* PatrolTarget;

	UPROPERTY(EditInstanceOnly, Category = "AI Navigation")
	TArray<AActor*> PatrolTargets;

	UPROPERTY(EditAnywhere)
	double  PatrolRadius = 100.f;

	FTimerHandle PatrolTimer;
	void PatrolTimerFinisher();

	UPROPERTY(EditAnywhere,Category="AI Navigation")
	float WaitMin = 5.f;

	UPROPERTY(EditAnywhere, Category = "AI Navigation")
	float WaitMax = 10.f;

	EEnemyState EnemyState = EEnemyState::EES_Patrolling;

protected:
	
	virtual void BeginPlay() override;

	void Die();

	bool InTargetRange(AActor* Target, double Radius);
	void MoveToTarget(AActor* Target);
	void CheckCombatTarget();
	void CheckPatrolTarget();
	AActor* ChoosePatrolTarget();

	UFUNCTION()
	void PawnSeen(APawn* PawnSeen);

	/*
	Play montage function
	*/
	void PlayHitReactMontage(const FName& SectionName);
	void DirectionalHitReact(const FVector& ImpactPoint);
    
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EDeathPose DeathPose = EDeathPose::EDP_Alive;
public:	
	
	

};
