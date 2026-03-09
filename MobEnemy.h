#pragma once

#include "EnemyBase.h"

using namespace KamataEngine;

class MobEnemy : public EnemyBase {
public:
	MobEnemy();
	virtual ~MobEnemy() override;

	void Initialize(const Camera* camera) override;
	void Update() override;
	void Draw() override;

private:
	int attack_;
	float speed_;

	Model* model_ = nullptr;
};
