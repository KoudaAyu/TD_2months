#include "IrisTransition.h"
#include <cmath>
#include <algorithm>

IrisTransition::IrisTransition() {}

IrisTransition::~IrisTransition() {}

void IrisTransition::Initialize() {
	// テクスチャ読み込み
	maskTexHandle_ = TextureManager::Load("iris_mask.png");
	whiteTexHandle_ = TextureManager::Load("white1x1.png");

	// 最大半径 = 画面の対角線の半分（円が画面全体を覆えるサイズ）
	maxRadius_ = std::sqrt(
		static_cast<float>(kScreenWidth * kScreenWidth + kScreenHeight * kScreenHeight)
	) / 2.0f;

	// 画面中心
	float cx = static_cast<float>(kScreenWidth) / 2.0f;
	float cy = static_cast<float>(kScreenHeight) / 2.0f;

	Vector4 black = {0.0f, 0.0f, 0.0f, 1.0f};

	// 円マスクスプライト（中心アンカー）
	circleSprite_.reset(
		Sprite::Create(maskTexHandle_, {cx, cy}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f})
	);

	// 周囲の黒スプライト（上下左右）
	topRect_.reset(Sprite::Create(whiteTexHandle_, {0.0f, 0.0f}, black, {0.0f, 0.0f}));
	bottomRect_.reset(Sprite::Create(whiteTexHandle_, {0.0f, 0.0f}, black, {0.0f, 0.0f}));
	leftRect_.reset(Sprite::Create(whiteTexHandle_, {0.0f, 0.0f}, black, {0.0f, 0.0f}));
	rightRect_.reset(Sprite::Create(whiteTexHandle_, {0.0f, 0.0f}, black, {0.0f, 0.0f}));
}

void IrisTransition::StartIrisOut(float durationSec) {
	state_ = State::IrisOut;
	timer_ = 0.0f;
	duration_ = durationSec;
	currentRadius_ = maxRadius_;
}

void IrisTransition::StartIrisIn(float durationSec) {
	state_ = State::IrisIn;
	timer_ = 0.0f;
	duration_ = durationSec;
	currentRadius_ = 0.0f;
}

void IrisTransition::Update() {
	if (state_ != State::IrisOut && state_ != State::IrisIn) {
		return;
	}

	const float deltaTime = 1.0f / 60.0f;
	timer_ += deltaTime;

	// smoothstep イージング
	float t = (std::min)(timer_ / duration_, 1.0f);
	float smooth = t * t * (3.0f - 2.0f * t);

	if (state_ == State::IrisOut) {
		// 円が縮小（max → 0）
		currentRadius_ = maxRadius_ * (1.0f - smooth);
	} else {
		// 円が拡大（0 → max）
		currentRadius_ = maxRadius_ * smooth;
	}

	// --- 円スプライトのサイズ更新 ---
	// 円マスク画像は正方形なので、直径 = currentRadius * 2
	float diameter = currentRadius_ * 2.0f;
	circleSprite_->SetSize({diameter, diameter});

	// --- 周囲の黒矩形を計算 ---
	float cx = static_cast<float>(kScreenWidth) / 2.0f;
	float cy = static_cast<float>(kScreenHeight) / 2.0f;

	// 円スプライトの画面上の矩形範囲
	float circleLeft = cx - currentRadius_;
	float circleRight = cx + currentRadius_;
	float circleTop = cy - currentRadius_;
	float circleBottom = cy + currentRadius_;

	// 上: 画面上端 ～ 円の上端
	float topH = (std::max)(circleTop, 0.0f);
	topRect_->SetPosition({0.0f, 0.0f});
	topRect_->SetSize({static_cast<float>(kScreenWidth), topH});

	// 下: 円の下端 ～ 画面下端
	float bottomY = (std::min)(circleBottom, static_cast<float>(kScreenHeight));
	float bottomH = static_cast<float>(kScreenHeight) - bottomY;
	bottomRect_->SetPosition({0.0f, bottomY});
	bottomRect_->SetSize({static_cast<float>(kScreenWidth), bottomH});

	// 左: 円の上端～下端の間、画面左端 ～ 円の左端
	float sideTop = (std::max)(circleTop, 0.0f);
	float sideBottom = (std::min)(circleBottom, static_cast<float>(kScreenHeight));
	float sideH = sideBottom - sideTop;

	float leftW = (std::max)(circleLeft, 0.0f);
	leftRect_->SetPosition({0.0f, sideTop});
	leftRect_->SetSize({leftW, sideH});

	// 右: 円の上端～下端の間、円の右端 ～ 画面右端
	float rightX = (std::min)(circleRight, static_cast<float>(kScreenWidth));
	float rightW = static_cast<float>(kScreenWidth) - rightX;
	rightRect_->SetPosition({rightX, sideTop});
	rightRect_->SetSize({rightW, sideH});

	// 完了チェック
	if (t >= 1.0f) {
		if (state_ == State::IrisIn) {
			// 円が開ききった → 描画不要
			state_ = State::None;
		} else {
			// 円が閉じきった → 黒画面を維持
			state_ = State::Finished;
		}
	}
}

void IrisTransition::Draw() {
	if (state_ == State::None) {
		return;
	}

	ID3D12GraphicsCommandList* cmdList = DirectXCommon::GetInstance()->GetCommandList();

	// 1. 周囲の黒矩形を通常ブレンドで描画
	Sprite::PreDraw(cmdList, Sprite::BlendMode::kNormal);
	topRect_->Draw();
	bottomRect_->Draw();
	leftRect_->Draw();
	rightRect_->Draw();
	Sprite::PostDraw();

	// 2. 円マスクを Multiply ブレンドで描画
	//    白い部分 → シーンがそのまま見える
	//    黒い部分 → シーンが黒くなる
	Sprite::PreDraw(cmdList, Sprite::BlendMode::kMultiply);
	circleSprite_->Draw();
	Sprite::PostDraw();
}
