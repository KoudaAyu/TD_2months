#include "SceneManager.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "ResultScene.h"

SceneManager::SceneManager() {}

SceneManager::~SceneManager() {}

void SceneManager::Initialize(IScene::SceneId startScene) {
	// アイリスエフェクト初期化
	iris_.Initialize();

	// 初期シーン生成
	currentScene_ = CreateScene(startScene);
	currentScene_->Initialize();

	// 最初のシーンはアイリスインで開始
	iris_.StartIrisIn(0.5f);
}

void SceneManager::Update() {
	if (!currentScene_) {
		return;
	}

	// アイリスエフェクト更新
	iris_.Update();

	if (isTransitioning_) {
		// アイリスアウト完了 → シーン切り替え → アイリスイン
		if (iris_.IsFinished()) {
			currentScene_ = CreateScene(pendingSceneId_);
			currentScene_->Initialize();
			pendingSceneId_ = IScene::SceneId::None;
			isTransitioning_ = false;

			// アイリスインで新シーンを表示
			iris_.StartIrisIn(0.5f);
		}
		// 遷移中はシーンの更新をしない
		return;
	}

	// 現在のシーンを更新
	currentScene_->Update();

	// シーン遷移リクエストがあればアイリスアウト開始
	IScene::SceneId nextId = currentScene_->GetNextSceneId();
	if (nextId != IScene::SceneId::None) {
		pendingSceneId_ = nextId;
		isTransitioning_ = true;
		iris_.StartIrisOut(0.5f);
	}
}

void SceneManager::Draw() {
	if (!currentScene_) {
		return;
	}

	// シーン描画
	currentScene_->Draw();

	// アイリスエフェクト描画（シーンの上に重ねる）
	iris_.Draw();
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
