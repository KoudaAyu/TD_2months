#include "GameScene.h"

GameScene::GameScene() {}

GameScene::~GameScene() {}

void GameScene::Initialize() {
	camera_.Initialize();
	mobEnemy_.Initialize(&camera_);
}

void GameScene::Update() {
	mobEnemy_.Update();
}

void GameScene::Draw() {
	mobEnemy_.Draw();
}



