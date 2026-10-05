#pragma once
#include "Projectile.h"

class PlayerProjectile : public Projectile
{
public:

	PlayerProjectile(Model* model) : Projectile(model){}

	void ShootProjectile(float x, float y);
};

