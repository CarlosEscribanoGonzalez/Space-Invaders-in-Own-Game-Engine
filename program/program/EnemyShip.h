#pragma once
#include "Model.h"
#include "ModelLoader.h"
#include "Projectile.h"
#include <string>

class EnemyShip
{
private:

	Model* enemy;
	bool state = true; 

public:

	EnemyShip(Model* model) : enemy(model) {}

	inline Model* GetEnemy() { return this->enemy; };
	inline bool GetState() { return this->state; };
	void SetState(bool state) { this->state = state; };
};