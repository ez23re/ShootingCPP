// Fill out your copyright notice in the Description page of Project Settings.


#include "DeadZoneActor.h"
#include "Components/BoxComponent.h"
#include "BulletActor.h"
#include "PlayerPawn.h"
#include "EnemyActor.h"

// Sets default values
ADeadZoneActor::ADeadZoneActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	SetRootComponent(BoxComp);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);

	BoxComp->SetMobility(EComponentMobility::Static);
	BoxComp->SetBoxExtent(FVector(50.0f));
	BoxComp->SetCollisionProfileName(TEXT("DeadZone"));
	BoxComp->OnComponentBeginOverlap.AddDynamic( this, &ADeadZoneActor::OnDeadZoneOverlap );

}

// Called when the game starts or when spawned
void ADeadZoneActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADeadZoneActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADeadZoneActor::OnDeadZoneOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerPawn* player = Cast<APlayerPawn>(OtherActor);
	if (player == nullptr) {
		OtherActor->Destroy();
	}

	AEnemyActor* enemy = Cast<AEnemyActor>(OtherActor);
	if (enemy != nullptr) {
		OtherActor->Destroy();
	}
	else {
		ABulletActor* bullet = Cast<ABulletActor>(OtherActor);
		if (bullet != nullptr) {
			OtherActor->Destroy();
		}
	}
}