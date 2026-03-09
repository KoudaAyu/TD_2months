#pragma once
#include "IScene.h"
#include <memory>

/// <summary>
/// シーンの生成・更新・描画・遷移を一元管理
/// </summary>
class SceneManager {
public:
	SceneManager();
	~SceneManager();

	/// 初期シーンを指定して初期化
	void Initialize(IScene::SceneId startScene);

	/// 毎フレーム更新
	void Update();

	/// 毎フレーム描画
	void Draw();

private:
	/// SceneId に応じたシーンを生成
	std::unique_ptr<IScene> CreateScene(IScene::SceneId id);

	std::unique_ptr<IScene> currentScene_;
};
