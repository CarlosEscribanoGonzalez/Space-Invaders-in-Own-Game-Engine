#pragma once
#include "Model.h"
#include "ModelLoader.h"
#include "Projectile.h"
#include <string>

class Player
{
private:

	Model* player;
	int lives;

public:

	Player(Model* playerArgument):player(playerArgument),lives(3) {}

	inline Model* GetPlayer(){return this->player;};
	inline int GetLives(){ return this->lives; };
	void SetLives(int lives) { this->lives = lives; };
	void Action(string command);
	float GetPosX();
	float GetPosY();
};
