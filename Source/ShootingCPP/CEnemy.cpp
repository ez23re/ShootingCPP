#include "CEnemy.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "CPlayerPawn.h"

ACEnemy::ACEnemy()
{
 	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComp->SetBoxExtent(FVector(50));
	SetRootComponent(BoxComp);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(BoxComp);

	BoxComp->SetCollisionProfileName(FName("Enemy"));
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ACEnemy::OnEnemyOverlap);
}

void ACEnemy::BeginPlay()
{
	Super::BeginPlay();
	

	float randValue = FMath::RandRange(1, 100);
	if (randValue <= randRate) {
		auto* player = GetWorld()->GetFirstPlayerController()->GetPawn();
		if (player != nullptr) {
			dir = player->GetActorLocation()-this->GetActorLocation();
		}
	}
	else {
		dir = GetActorForwardVector();
	}
} 

void ACEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector p0 = GetActorLocation();
	SetActorLocation(p0 + dir * Speed * DeltaTime);
}

void ACEnemy::OnEnemyOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	ACPlayerPawn* player = Cast<ACPlayerPawn>(OtherActor);
	if (player) {
		OtherActor->Destroy();
	}this->Destroy();
}