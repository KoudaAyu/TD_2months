#pragma once
#include "KamataEngine.h"
#include <memory>

using namespace KamataEngine;

/// <summary>
/// アイリス遷移エフェクト（円形ワイプ）
/// </summary>
class IrisTransition {
public:
	/// 遷移の状態
	enum class State {
		None,     // エフェクトなし
		IrisOut,  // 円が閉じていく
		IrisIn,   // 円が開いていく
		Finished, // エフェクト完了
	};

	IrisTransition();
	~IrisTransition();

	/// 初期化
	void Initialize();

	/// アイリスアウト開始（円が閉じる）
	void StartIrisOut(float durationSec = 0.5f);

	/// アイリスイン開始（円が開く）
	void StartIrisIn(float durationSec = 0.5f);

	/// 更新
	void Update();

	/// 描画（Sprite::PreDraw/PostDraw の外で呼ぶ）
	void Draw();

	/// 現在の状態を取得
	State GetState() const { return state_; }

	/// エフェクトが完了したか
	bool IsFinished() const { return state_ == State::Finished; }

	/// エフェクトが動作中か
	bool IsActive() const { return state_ == State::IrisOut || state_ == State::IrisIn; }

private:
	// 画面サイズ
	static const int kScreenWidth = 1280;
	static const int kScreenHeight = 720;

	// 状態
	State state_ = State::None;

	// タイマー
	float timer_ = 0.0f;
	float duration_ = 0.5f;

	// 現在の円の半径
	float currentRadius_ = 0.0f;

	// 最大半径
	float maxRadius_ = 0.0f;

	// テクスチャハンドル
	uint32_t maskTexHandle_ = 0;
	uint32_t whiteTexHandle_ = 0;

	// 円マスクスプライト（Multiply ブレンドで描画）
	std::unique_ptr<Sprite> circleSprite_;

	// 周囲を埋める黒スプライト（上下左右の4枚）
	std::unique_ptr<Sprite> topRect_;
	std::unique_ptr<Sprite> bottomRect_;
	std::unique_ptr<Sprite> leftRect_;
	std::unique_ptr<Sprite> rightRect_;
};
