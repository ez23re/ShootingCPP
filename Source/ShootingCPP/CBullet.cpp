#include "CBullet.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "CEnemy.h"

ACBullet::ACBullet()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>("BoxComp");
	BoxComp->SetBoxExtent(FVector(50));
	SetRootComponent(BoxComp);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	MeshComp->SetupAttachment(BoxComp);


	BoxComp->SetCollisionProfileName(FName("Bullet"));
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ACBullet::OnBulletOverlap);
}

void ACBullet::BeginPlay()
{
	Super::BeginPlay();

}

void ACBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	SetActorLocation(GetActorLocation() + Speed * DeltaTime * GetActorForwardVector());
}

void ACBullet::OnBulletOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACEnemy* enemy = Cast<ACEnemy>(OtherActor);
	if (enemy) {
		OtherActor->Destroy();
	}this->Destroy();
}
