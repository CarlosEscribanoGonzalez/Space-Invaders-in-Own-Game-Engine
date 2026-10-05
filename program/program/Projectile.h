#pragma once
#include "Model.h"
class Projectile
{
protected:
    Model* model;

public:
    Projectile(Model* model) : model(model) {}

    Model* GetModel() { return this->model; };
    virtual void ShootProjectile(float x, float y) = 0;
};

