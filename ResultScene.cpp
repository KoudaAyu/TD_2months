#include "ResultScene.h"
#include "KamataEngine.h"

using namespace KamataEngine;

ResultScene::ResultScene() {}

ResultScene::~ResultScene() {}

void ResultScene::Initialize() {
	// TODO: リザルト画面の初期化（スコア表示用スプライトなど）
}

void ResultScene::Update() {
	// SPACEキーでタイトルへ戻る
	if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
		ChangeScene(SceneId::Title);
	}
}

void ResultScene::Draw() {
	// TODO: リザルト画面の描画
}
