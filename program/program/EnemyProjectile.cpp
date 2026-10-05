#include "EnemyProjectile.h"

void EnemyProjectile::ShootProjectile(float x, float y)
{
	this->model->SetPosition(Vector3D(x, y, 0));

	float orientation = rand() % 20 - 10; //In degrees
	this->model->SetOrientation(Vector3D(0, 0, orientation));

	orientation = orientation * 3.1415 / 180; //To radians
	this->model->SetSpeed(Vector3D(0.5 * sin(orientation), -0.5 * cos(orientation), 0.0)); //Velocity is calculated in both axis
}