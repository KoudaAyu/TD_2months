#include "SceneManager.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "ResultScene.h"

SceneManager::SceneManager() {}

SceneManager::~SceneManager() {}

void SceneManager::Initialize(IScene::SceneId startScene) {
	currentScene_ = CreateScene(startScene);
	currentScene_->Initialize();
}

void SceneManager::Update() {
	if (!currentScene_) {
		return;
	}

	// 現在のシーンを更新
	currentScene_->Update();

	// シーン遷移リクエストがあれば処理
	IScene::SceneId nextId = currentScene_->GetNextSceneId();
	if (nextId != IScene::SceneId::None) {
		currentScene_ = CreateScene(nextId);
		currentScene_->Initialize();
	}
}

void SceneManager::Draw() {
	if (!currentScene_) {
		return;
	}
	currentScene_->Draw();
}

std::unique_ptr<IScene> SceneManager::CreateScene(IScene::SceneId id) {
	switch (id) {
	case IScene::SceneId::Title:
		return std::make_unique<TitleScene>();
	case IScene::SceneId::Game:
		return std::make_unique<GameScene>();
	case IScene::SceneId::Result:
		return std::make_unique<ResultScene>();
	default:
		return nullptr;
	}
}
