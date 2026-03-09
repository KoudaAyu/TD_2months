#pragma once
#include"KamataEngine.h"


using namespace KamataEngine;

class EnemyBase {
public:
	EnemyBase();
	virtual ~EnemyBase();

	// Initialize with camera from GameScene
	virtual void Initialize(const Camera* camera);
	virtual void Update();
	virtual void Draw();

	void SetPosition(const Vector3& pos);
	void GetPosition(Vector3& pos) const;
	void SetVelocity(const Vector3& vel);
	void GetVelocity(Vector3& vel) const;

	void Damage(int amount);
	int GetHP() const;
	bool IsActive() const;
	void Kill();

protected:
	Vector3 position_;
	Vector3 velocity_;
	int hp_;
	bool active_;

	Camera* camera_;
	WorldTransform worldTransform_;
};
