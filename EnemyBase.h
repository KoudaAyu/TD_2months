#pragma once

#include "Transform.h"

class EnemyBase {
public:
	EnemyBase();
	virtual ~EnemyBase();

	// Lifecycle
	virtual void Initialize();
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

private:
	Vector3 position_;
	Vector3 velocity_;
	int hp_;
	bool active_;
};
