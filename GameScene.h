#pragma once

#include "MobEnemy.h"

using namespace KamataEngine;

class GameScene {
public:
	GameScene();
	~GameScene();
	void Initialize();
	void Update();
	void Draw();

private:
	MobEnemy mobEnemy_;

	Camera camera_;
};
