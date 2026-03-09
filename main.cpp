#include <Windows.h>
#include "KamataEngine.h"
#include "SceneManager.h"

using namespace KamataEngine;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	// エンジンの初期化
	KamataEngine::Initialize();

	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	SceneManager sceneManager;
	sceneManager.Initialize(IScene::SceneId::Title);

	while (true) {
		if (KamataEngine::Update()) {
			break;
		}

		sceneManager.Update();

		dxCommon->PreDraw();

		sceneManager.Draw();

		dxCommon->PostDraw();
	}

	KamataEngine::Finalize();
	return 0;
}
