#include "TitleScene.h"
#include "KamataEngine.h"

using namespace KamataEngine;

TitleScene::TitleScene() {}

TitleScene::~TitleScene() {}

void TitleScene::Initialize() {
	// TODO: タイトル画面の初期化（スプライト読み込みなど）
}

void TitleScene::Update() {
	// SPACEキーでゲームシーンへ遷移
	if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
		ChangeScene(SceneId::Game);
	}
}

void TitleScene::Draw() {
	// TODO: タイトル画面の描画
}
