#include "CPlayerPawn.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"

ACPlayerPawn::ACPlayerPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>("BoxComp");
	BoxComp->SetBoxExtent(FVector(50));
	SetRootComponent(BoxComp);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	MeshComp->SetupAttachment(BoxComp);

	FirePosition = CreateDefaultSubobject<UArrowComponent>("FirePosition");
	FirePosition->SetupAttachment(BoxComp);
	FirePosition->SetRelativeLocationAndRotation(FVector(0, 0, 100), FRotator(90, 0, 0));

	BoxComp->SetCollisionProfileName(FName("Player"));
}


void ACPlayerPawn::BeginPlay()
{
	Super::BeginPlay();

}

void ACPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetActorLocation(GetActorLocation() + Speed * DeltaTime * (FVector(0, h, v)).GetSafeNormal());
}

void ACPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Horizontal"), this, &ACPlayerPawn::OnHorizontal);
	PlayerInputComponent->BindAxis(TEXT("Vertical"), this, &ACPlayerPawn::OnVertical);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ACPlayerPawn::OnFire);
}

void ACPlayerPawn::OnHorizontal(float value)
{
	h = value;
}

void ACPlayerPawn::OnVertical(float value)
{
	v = value;
}

void ACPlayerPawn::OnFire()
{
	FTransform FirePos = FirePosition->GetComponentTransform();
	GetWorld()->SpawnActor<ACBullet>(BulletFactory, FirePos);
}
