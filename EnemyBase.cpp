#include "EnemyBase.h"

EnemyBase::EnemyBase()
	: position_{0.0f, 0.0f, 0.0f}
	, velocity_{0.0f, 0.0f, 0.0f}
	, hp_(1)
	, active_(true)
{
}

EnemyBase::~EnemyBase() = default;

void EnemyBase::Initialize() {
	position_ = {0.0f, 0.0f, 0.0f};
	velocity_ = {0.0f, 0.0f, 0.0f};
	hp_ = 1;
	active_ = true;
}

void EnemyBase::Update() {
	position_.x += velocity_.x;
	position_.y += velocity_.y;

	if (hp_ <= 0) {
		active_ = false;
	}
}

void EnemyBase::Draw() {

}

void EnemyBase::SetPosition(const Vector3 &pos) { position_ = pos; }
void EnemyBase::GetPosition(Vector3 &pos) const { pos = position_; }
void EnemyBase::SetVelocity(const Vector3 &vel) { velocity_ = vel; }
void EnemyBase::GetVelocity(Vector3 &vel) const { vel = velocity_; }

void EnemyBase::Damage(int amount) {
	hp_ -= amount;
	if (hp_ <= 0) {
		Kill();
	}
}

int EnemyBase::GetHP() const { return hp_; }
bool EnemyBase::IsActive() const { return active_; }
void EnemyBase::Kill() { active_ = false; }
