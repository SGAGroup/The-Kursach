#include "MapGenerator.h"
#include "Kismet/GameplayStatics.h"

#pragma region preset
AMapGenerator::AMapGenerator()
{
	PrimaryActorTick.bCanEverTick = true;
}
void AMapGenerator::BeginPlay()
{
	Super::BeginPlay();
	Init();
}
void AMapGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Каждый тик проверяем нужно ли удалять старое/спавнить новое
	UpdatePlayerPos();
	//MapCheck();
	BoundsCheck();

	mPrevPos = mPlayerPos;
}

#pragma endregion

void AMapGenerator::Init() {
	//Считаем размер платформ
	FVector center, extend;
	AActor* example = GetWorld()->SpawnActor<AActor>(mPlatform, FVector(0, 0, 0), FRotator());
	example->GetActorBounds(false, center, extend);
	example->Destroy();
	double size_x = abs(extend.X - center.X) * 2;
	double size_y = abs(extend.Y - center.Y) * 2;
	double middle_size = (size_x + size_y) / 2;
	mPlatformSize = middle_size;
	mRadiusInUnits = middle_size * mRadius;
	UE_LOG(LogTemp, Warning, TEXT("[spawning] size: %d, radius: %d"), mPlatformSize, mRadiusInUnits);

	//Получаем игрока
	mPlayerSpawnPos = UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetActorLocation();
	UpdatePlayerPos();
	//Начинаем генерировать
	StartGenerate();
}

void AMapGenerator::StartGenerate() {
	double playerZ = mPlayerPos.Z;
	mHeightLevel = playerZ - 50;

	for (int y = -mRadius; y < mRadius; ++y)
		for (int x = -mRadius; x < mRadius; ++x) {
			UE_LOG(LogTemp, Warning, TEXT("[spawning] x: %d, y: %d"), x, y);
			Platform newPlatform = makePlatform(x, y);
			mSpawnedPlatforms.Push(newPlatform);
		}
}

void AMapGenerator::MapCheck()
{
	/*
		Нерационально. Можно лучше.
	*/

	FVector2d playerPosCell = unitsPosToAbstract(mPlayerPos);
	FVector2d prevPosCell = unitsPosToAbstract(mPrevPos);

	if (playerPosCell == prevPosCell) return;

	//удаляем лишние
	for (auto block : mSpawnedPlatforms)
	{
		FVector2d vector_to_block = block.position - playerPosCell;
		double distance_to_block = vector_to_block.Length();
		
		if (distance_to_block > mRadius) {
			mSpawnedPlatforms.Remove(block);
			block.actor->Destroy();
		}
	}


	//spawning new platforms
	for(int x = playerPosCell.X - mRadius; x < playerPosCell.X + mRadius; ++x)
		for (int y = playerPosCell.Y - mRadius; y < playerPosCell.Y + mRadius; ++y) {			
			FVector2d pos = FVector2d(x, y); 
			if (ifAlreadySpawned(pos)) break; //if platform with given pos already in array -> skip

			Platform newPlatform = makePlatform(x, y);
			mSpawnedPlatforms.Push(newPlatform);
		}

}

void AMapGenerator::UpdatePlayerPos()
{
	mPlayerPos = UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetActorLocation();
}

FVector2d AMapGenerator::unitsPosToAbstract(FVector3d pos) {
	FVector2d result = FVector2d(floor(pos.X / mPlatformSize), floor(pos.Z / mPlatformSize));
	return result;
}

AMapGenerator::Platform AMapGenerator::makePlatform(int x, int y)
{
	FVector pos = FVector(x * mPlatformSize, y * mPlatformSize, mHeightLevel);

	AActor* newPlatform = GetWorld()->SpawnActor<AActor>(mPlatform, pos, FRotator());
	newPlatform->SetOwner(this);

	Platform newCell = { FVector2d(x,y), newPlatform };
	return newCell;
}

bool AMapGenerator::ifAlreadySpawned(FVector2d pos) {
	bool res = false;
	for (auto p : mSpawnedPlatforms){
		res = p.position == pos;
		if (res) break;
	}
	return res;
}

void AMapGenerator::BoundsCheck() {
	auto deltaPos = (mPlayerPos - mPlayerSpawnPos);
	deltaPos.Z = 0;

	if (deltaPos.Length() < (mRadiusInUnits - mPlatformSize*2)) return;

	auto reverseVector = -deltaPos;
	UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->SetActorLocation(mPlayerSpawnPos + reverseVector*0.9);
}