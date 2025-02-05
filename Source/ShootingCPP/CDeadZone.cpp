#include "CDeadZone.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "CEnemy.h"
#include "CPlayerPawn.h"
#include "CBullet.h"

ACDeadZone::ACDeadZone()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComp->SetBoxExtent(FVector(50));
	SetRootComponent(BoxComp);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(BoxComp);

	BoxComp->SetCollisionProfileName(FName("DeadZone"));
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ACDeadZone::OnDeadZoneOverlap);
}

void ACDeadZone::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACDeadZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACDeadZone::OnDeadZoneOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACEnemy* enemy = Cast<ACEnemy>(OtherActor);
	if (enemy) {
		OtherActor->Destroy();
	}

	ACBullet* bullet = Cast<ACBullet>(OtherActor);
	if (bullet) {
		OtherActor->Destroy();
	}
}
