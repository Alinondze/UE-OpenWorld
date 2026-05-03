

#include "Enemy/Enemy.h"
#include "AIController.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"
#include "HUD/HealthBarComponent.h"
#include "NavigationPath.h"
#include "Navigation/PathFollowingComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "AITypes.h"
#include "Components/AttributeComponent.h"
#include "Items/Weapons/Weapon.h"

AEnemy::AEnemy()
{
 	
	PrimaryActorTick.bCanEverTick = true;
	GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	GetMesh()->SetGenerateOverlapEvents(true);

	
	HealthBarWidget = CreateDefaultSubobject<UHealthBarComponent>(TEXT("HealthBar"));
	HealthBarWidget->SetupAttachment(GetRootComponent());

	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationPitch = false; 
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensing"));
	PawnSensing->SightRadius = 4000.f;
	PawnSensing->SetPeripheralVisionAngle(45.f);
}


void AEnemy::PatrolTimerFinisher()
{
	MoveToTarget(PatrolTarget);

}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	if (HealthBarWidget)
	{
		HealthBarWidget->SetVisibility(false);
	}
	GetCharacterMovement()->MaxWalkSpeed = 58.f;
	EnemyController = Cast<AAIController>(GetController());
	MoveToTarget(PatrolTarget);

	if (PawnSensing)
	{
		PawnSensing->OnSeePawn.AddDynamic(this, &AEnemy::PawnSeen);
	}

	UWorld* World = GetWorld();
	if (World && WeaponClass)
	{
		AWeapon* DefaultWeapon = World->SpawnActor<AWeapon>(WeaponClass);
		DefaultWeapon->Equip(GetMesh(), FName("RightHandSocket"), this, this);
		EquippedWeapon = DefaultWeapon;
	}
	}
   
void AEnemy::Die()
{
 //TODO: Play Death Montage
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && DeathMontage)
	{
		AnimInstance->Montage_Play(DeathMontage);

		const int32 Selection = FMath::RandRange(0, 3);
		FName SectionName = FName();
		switch (Selection)
		{
		case 0:
			SectionName = FName("Death1");
			DeathPose = EDeathPose::EDP_Death1;
			break;
		case 1:
			SectionName = FName("Death2");
			DeathPose = EDeathPose::EDP_Death2;
			break;
		case 2:
			SectionName = FName("Death3");
			DeathPose = EDeathPose::EDP_Death3;
			break;
		case 3:
			SectionName = FName("Death4");
			DeathPose = EDeathPose::EDP_Death4;
			break;
		default:
			break;
		}

		AnimInstance->Montage_JumpToSection(SectionName, DeathMontage);
	}
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetLifeSpan(3.f);
}


bool AEnemy::InTargetRange(AActor* Target, double Radius)
{
	if (Target == nullptr) return false;
	const double DistanceToTarget = (Target->GetActorLocation() - GetActorLocation()).Size();
	return DistanceToTarget<=Radius;
}

void AEnemy::MoveToTarget(AActor* Target)
{
	if (EnemyController == nullptr || Target == nullptr) return;
	
		FAIMoveRequest MoveRequest;
		MoveRequest.SetGoalActor(Target);
		MoveRequest.SetAcceptanceRadius(25.f);
		EnemyController->MoveTo(MoveRequest);
		
}

AActor* AEnemy::ChoosePatrolTarget()
{
	
			TArray<AActor*> ValidTargets;


			for (auto Target : PatrolTargets)
			{
				if (Target != PatrolTarget)
				{
					ValidTargets.AddUnique(Target);
				}
			}
			const int32 NumPatrolTargets = ValidTargets.Num();
			if (NumPatrolTargets > 0)
			{
				const int32 TargetSelection = FMath::RandRange(0, NumPatrolTargets - 1);
				return ValidTargets[TargetSelection];
				
		    }

	
	return nullptr;
}

void AEnemy::PawnSeen(APawn* SeenPawn)
{
	if (EnemyState == EEnemyState::EES_Chasing) return;
	if (SeenPawn->ActorHasTag(FName("SlashCharacter")))
	{
		
		GetWorldTimerManager().ClearTimer(PatrolTimer);
		GetCharacterMovement()->MaxWalkSpeed = 300.f;
		CombatTarget = SeenPawn;

		if (EnemyState != EEnemyState::EES_Attacking)
		{
         EnemyState = EEnemyState::EES_Chasing;
		 MoveToTarget(CombatTarget);
         UE_LOG(LogTemp, Warning, TEXT("Seen Pawn,now Chasing"));
		}
		
	}
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (EnemyState > EEnemyState::EES_Patrolling)
	{
        CheckCombatTarget();
	}
	else
	{ 
		CheckPatrolTarget();
	}
	
 
}

void AEnemy::CheckPatrolTarget()
{
	if (InTargetRange(PatrolTarget, PatrolRadius))
	{
		PatrolTarget = ChoosePatrolTarget();
		const float WaitTime = FMath::RandRange(WaitMin, WaitMax);
		GetWorldTimerManager().SetTimer(PatrolTimer, this, &AEnemy::PatrolTimerFinisher, WaitTime);
	}

}

void AEnemy::CheckCombatTarget()
{
	if (!InTargetRange(CombatTarget, CombatRadius))
	{
		//Outside combat radius,lose interest
		CombatTarget = nullptr;
		if (HealthBarWidget)
		{
			HealthBarWidget->SetVisibility(false);
		}
		EnemyState = EEnemyState::EES_Patrolling;
		GetCharacterMovement()->MaxWalkSpeed = 125.f;
		MoveToTarget(PatrolTarget);
		
	}	else if (!InTargetRange(CombatTarget, AttackRadius)&& EnemyState !=EEnemyState::EES_Chasing)
	{
		//Outside attack range,chase character
		EnemyState = EEnemyState::EES_Chasing;
		GetCharacterMovement()->MaxWalkSpeed = 300.f;
		MoveToTarget(CombatTarget);
		
	}
	else if (InTargetRange(CombatTarget, AttackRadius) && EnemyState != EEnemyState::EES_Attacking)
	{
		//Inside attack range,attack character
		EnemyState = EEnemyState::EES_Attacking;
		//TODO: Attack montage
		
	}
}

void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::GetHit_Implementation(const FVector& ImpactPoint)
{

	//UWorld* World = GetWorld();
	//if (World)
	//{
		//DrawDebugSphere(
			//World,             // світ
		//	ImpactPoint,          // центр сфери
			//10.f,              // радіус
		//	24,                // сегменти (int32!)
		//	FColor::Red,       // колір
		//	false,             // persistent lines?
		//	5.f               // тривалість
		//);

	//}
	 
	if (HealthBarWidget)
	{
		HealthBarWidget->SetVisibility(true);
	}

	if (Attributes && Attributes->IsAlive())
	{
	  DirectionalHitReact(ImpactPoint);
	}
	else
	{
		Die();
	}
	
	if (HitSound)
	{
		UGameplayStatics::PlaySoundAtLocation(
			this,
			HitSound,
			ImpactPoint
		);
	}
	if (HitParticles && GetWorld())
	{
		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			HitParticles,
			ImpactPoint

		);
	}
}


 float AEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCause)
 {
	 if (Attributes && HealthBarWidget)
	 {
		 Attributes->ReceiveDamage(DamageAmount);
		 HealthBarWidget->SetHealthPercent(Attributes->GetHealthPercent());
		 
	 }
	 CombatTarget = EventInstigator->GetPawn();
	 EnemyState = EEnemyState::EES_Chasing;
	 GetCharacterMovement()->MaxWalkSpeed = 300.f;
	 MoveToTarget(CombatTarget);
	 return DamageAmount;
 }

 void AEnemy::Destroyed()
 {
	 if (EquippedWeapon)
	 {
		 EquippedWeapon->Destroy();
	 }
 }

