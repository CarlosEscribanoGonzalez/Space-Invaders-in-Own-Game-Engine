#include "PlayerProjectile.h"

void PlayerProjectile::ShootProjectile(float x, float y)
{
	this->model->SetPosition(Vector3D(x, y, 0));
	this->model->SetSpeed(Vector3D(0, 0.7, 0));
}