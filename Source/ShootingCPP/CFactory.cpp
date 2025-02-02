#include "CFactory.h"
#include "Components/ArrowComponent.h"
#include "CEnemy.h"

ACFactory::ACFactory()
{
	PrimaryActorTick.bCanEverTick = true;

	EnemyPosition = CreateDefaultSubobject<UArrowComponent>(TEXT("EnemyPosition"));
	EnemyPosition->SetRelativeLocationAndRotation(FVector(0), FRotator(-90, 0, 0));
	SetRootComponent(EnemyPosition);
	
}

void ACFactory::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACFactory::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentTime += DeltaTime;
	if (CurrentTime >= DelayTime) {
		MakeEnemy();
		CurrentTime = 0.0f;
	}
}

void ACFactory::MakeEnemy()
{
	FTransform EnemyPos = EnemyPosition->GetComponentTransform();
	GetWorld()->SpawnActor<ACEnemy>(EnemyFactory, EnemyPos);
}