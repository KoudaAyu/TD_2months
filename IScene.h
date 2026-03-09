#pragma once

/// <summary>
/// シーンの基底インターフェース
/// </summary>
class IScene {
public:
	/// シーンID（シーン遷移用）
	enum class SceneId {
		Title,
		Game,
		Result,
		None, // 遷移なし
	};

	virtual ~IScene() = default;

	/// 初期化
	virtual void Initialize() = 0;
	/// 更新
	virtual void Update() = 0;
	/// 描画
	virtual void Draw() = 0;

	/// 次に遷移すべきシーンIDを返す
	SceneId GetNextSceneId() const { return nextSceneId_; }

protected:
	/// 派生クラスがシーン遷移をリクエストするために呼ぶ
	void ChangeScene(SceneId id) { nextSceneId_ = id; }

private:
	SceneId nextSceneId_ = SceneId::None;
};
