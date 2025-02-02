#include "CFactory.h"
#include "Components/ArrowComponent.h"
#include "CEnemy.h"

ACFactory::ACFactory()
{
	PrimaryActorTick.bCanEverTick = true;	

	EnemyPosition = CreateDefaultSubobject<UArrowComponent>(TEXT("EnemyPosition"));
	EnemyPosition->SetupAttachment(RootComponent);
	EnemyPosition->SetRelativeLocationAndRotation(FVector(0, 0, 100), FRotator(-90, 0, 0));
}

void ACFactory::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACFactory::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	CurTime += DeltaTime;
	if (CurTime >= DelTime) {
		MakeEnemy();
		CurTime = 0.0f;
	}
}

void ACFactory::MakeEnemy()
{
	FTransform EnemyPos = EnemyPosition->GetComponentTransform();
	GetWorld()->SpawnActor<ACEnemy>(Enemy, EnemyPos);
}