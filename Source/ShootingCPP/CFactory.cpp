#include "CFactory.h"
#include "Components/ArrowComponent.h"

ACFactory::ACFactory()
{
	PrimaryActorTick.bCanEverTick = true;

	EnemyPosition = CreateDefaultSubobject<UArrowComponent>("EnemyPosition");
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
	cur += DeltaTime;
	if (cur >= del) {
		FTransform EnemyPos = EnemyPosition->GetComponentTransform();
		GetWorld()->SpawnActor<ACEnemy>(EnemyFactory, EnemyPos);
		cur = 0.f;
	}
}