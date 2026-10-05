#include "GameOverScene.h"

void GameOverScene::Init()
{
	camera.SetPosition(Vector3D(5, 4, 18));
	gameOverText = new Text(Vector3D(4.5, 4.5, 6.5), "Game Over");
	restartInfo = new Text(Vector3D(3.0, 1.5, 6.5), "Press 'r' to play again");
	this->AddGameObject(gameOverText);
	this->AddGameObject(restartInfo);
}

void GameOverScene::Render()
{
	this->camera.Render();

	for (int idx = 0; idx < this->gameObjects.size(); idx++)
	{
		this->gameObjects[idx]->Render();
	}
}

void GameOverScene::Update(const float& time, int& puntos)
{
	points = puntos;
	this->camera.Update(time);

	this->RemoveGameObject(this->finalPointsText);
	finalPointsText = new Text(Vector3D(4.1, 3, 6.5), "Points: " + std::to_string(points));
	this->AddGameObject(finalPointsText);

	for (int idx = 0; idx < this->gameObjects.size(); idx++)
	{
		this->gameObjects[idx]->Update(time);
	}
}

void GameOverScene::ProcessKeyPressed(unsigned char key, int px, int py)
{
	if (key == 'r' || key == 'R') restart = true;
}

int GameOverScene::GetNextScene()
{
	if (restart)
	{
		restart = false;
		return 0;
	}
	else return 1;
}