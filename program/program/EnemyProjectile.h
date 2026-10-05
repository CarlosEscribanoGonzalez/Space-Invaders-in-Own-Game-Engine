#pragma once
#include "Projectile.h"

class EnemyProjectile : public Projectile
{
public:

	EnemyProjectile(Model* model) : Projectile(model){}

	void ShootProjectile(float x, float y);
};


