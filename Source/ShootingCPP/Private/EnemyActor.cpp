// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PlayerPawn.h"

// Sets default values
AEnemyActor::AEnemyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	SetRootComponent(BoxComp);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);

	BoxComp->SetCollisionProfileName(TEXT("Enemy"));
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &AEnemyActor::OnEnemyOverlap);
}

// Called when the game starts or when spawned
void AEnemyActor::BeginPlay()
{
	Super::BeginPlay();

	// �¾ �� ������ ���ϰ� 30%�� �÷��̾ ���ؼ�, �ƴҰ�� ����
	int32 randValue = FMath::RandRange(1, 100);

	if (randValue <= RandomRate) {
		auto* player = GetWorld()->GetFirstPlayerController()->GetPawn();

		if (player != nullptr) {
			Direction = player->GetActorLocation() - this->GetActorLocation();
			Direction.Normalize();
		}
		else {
			Direction = GetActorForwardVector();
		}
	}
	
}

// Called every frame
void AEnemyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetActorLocation(GetActorLocation() + Direction * Speed * DeltaTime);
}

void AEnemyActor::OnEnemyOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerPawn* player = Cast<APlayerPawn>(OtherActor);
	if (player != nullptr) {
		OtherActor->Destroy();
		this->Destroy();
	}
}

