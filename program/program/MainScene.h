#pragma once
#include "Scene.h"
#include "Player.h"
#include "PlayerProjectile.h"
#include "EnemyProjectile.h"
#include "EnemyShip.h"

class MainScene : public Scene
{
private:
	bool isProjectileActive;
	bool gameOver;
	bool changeDir;
	bool pressedLeft;
	bool pressedRight;
	float gameSpeed;
	int timer;
	int points;

	Player* player;
	PlayerProjectile* playerProjectile;
	EnemyProjectile* enemyProjectile;
	vector<EnemyShip*> enemies;
	Text* pointsText;
	Text* livesText;

public:
	MainScene() : isProjectileActive(true), changeDir(false), gameOver(false), 
		pressedLeft(false), pressedRight(false), gameSpeed(0.05), timer(0), points(0) {}

	void Init();
	void Render();
	void Update(const float& time, int& puntos);
	void ProcessKeyPressed(unsigned char key, int px, int py);
	void ProcessKeyReleased(unsigned char key, int px, int py);
	void ProcessKeyArrows(unsigned char key, int px, int py);
	void ProcessKeyArrowsUp(unsigned char key, int px, int py);
	void RestartMainScene();
	void ImpactAlien();
	void AlienMovement();
	void ImpactPlayer();
	void Shoot_Alien();
	int GetNextScene();
};
