#pragma once
#include "IScene.h"

/// <summary>
/// タイトルシーン
/// </summary>
class TitleScene : public IScene {
public:
	TitleScene();
	~TitleScene() override;

	void Initialize() override;
	void Update() override;
	void Draw() override;
};
