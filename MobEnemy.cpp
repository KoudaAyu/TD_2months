#include "MobEnemy.h"

MobEnemy::MobEnemy()
	: EnemyBase()
	, attack_(1)
	, speed_(1.0f)
{
}

MobEnemy::~MobEnemy() = default;

void MobEnemy::Initialize(const Camera* camera) {

	EnemyBase::Initialize(camera);
	attack_ = 2;
	speed_ = 1.5f;

	model_ = Model::Create();

}

void MobEnemy::Update() {
	
	velocity_.x = -speed_;
	EnemyBase::Update();

	
	if (position_.x < -100.0f) {
		active_ = false;
	}
}

void MobEnemy::Draw() { 
	if (camera_) {
		model_->Draw(worldTransform_, *camera_);
	}
}
