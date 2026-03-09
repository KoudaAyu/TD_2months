#pragma once
#include "IScene.h"

/// <summary>
/// リザルトシーン
/// </summary>
class ResultScene : public IScene {
public:
	ResultScene();
	~ResultScene() override;

	void Initialize() override;
	void Update() override;
	void Draw() override;
};
