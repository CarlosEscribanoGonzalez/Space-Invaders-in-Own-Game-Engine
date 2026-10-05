#include "MainScene.h"

void MainScene::Init()
{
	camera.SetPosition(Vector3D(5, 4, 18));

	ModelLoader* loader = new ModelLoader(0.1f);
	Model* playerShip = new Model();
	loader->LoadModel("..\\..\\3dModels\\playerShip.obj");
	*playerShip = loader->GetModel();
	playerShip->PaintColor();
	playerShip->SetPosition(Vector3D(5, -5, 0));
	playerShip->SetOrientation(Vector3D(-90, 90, 0));
	player = new Player(playerShip);
	this->AddGameObject(playerShip);

	loader->Clear();

	loader = new ModelLoader(0.4f);
	Model* playerProj = new Model();
	loader->LoadModel("..\\..\\3dModels\\rocket.obj");
	*playerProj = loader->GetModel();
	playerProj->PaintColor();
	playerProj->SetPosition(Vector3D(0, -10.0, 0.0));
	playerProj->SetOrientation(Vector3D(0, 90, 0.0));
	playerProjectile = new PlayerProjectile(playerProj);
	this->AddGameObject(playerProj);

	loader->Clear();
	

	loader = new ModelLoader(0.3f);
	Model* enemyProj = new Model();
	loader->LoadModel("..\\..\\3dModels\\rocket.obj");
	*enemyProj = loader->GetModel();
	enemyProj->PaintColor();
	enemyProj->SetPosition(Vector3D(0.0, -10.0, 0.0));
	enemyProj->SetOrientation(Vector3D(180, 90, 0.0));
	this->enemyProjectile = new EnemyProjectile(enemyProj);
	this->AddGameObject(enemyProj);

	loader->Clear();

	for (int i = 0; i < 33; ++i) {
		loader = new ModelLoader(0.5f);
		Model* ufo = new Model();
		loader->LoadModel("..\\..\\3dModels\\ufo.obj");
		*ufo = loader->GetModel();
		if (i < 11)
		{
			ufo->SetPosition(Vector3D(-1 + i * 1.1, 13, 0));
		}
		else if (i < 22 && i >= 11)
		{
			ufo->SetPosition(Vector3D(this->enemies[i - 11]->GetEnemy()->GetPosition().GetX(), 12, 0));
		}
		else if (i < 33 && i >= 22)
		{
			ufo->SetPosition(Vector3D(this->enemies[i - 11]->GetEnemy()->GetPosition().GetX(), 11, 0));
		}

		if (gameSpeed <= 0.20)
		{
			ufo->SetSpeed(Vector3D(0.1 + gameSpeed, 0.0, 0.0));
		}
		else
		{
			ufo->SetSpeed(Vector3D(0.3, 0.0, 0.0));
		}
		
		ufo->PaintColor();
		EnemyShip* enemyship = new EnemyShip(ufo);
		this->enemies.push_back(enemyship);
		this->AddGameObject(ufo);

		loader->Clear();
	}
}

void MainScene::Render()
{
	this->camera.Render();

	for (int idx = 0; idx < this->gameObjects.size(); idx++)
	{
		this->gameObjects[idx]->Render();
	}
}

void MainScene::Update(const float& time, int& pts)
{
	pts = points;

	this->camera.Update(time);

	for (int idx = 0; idx < this->gameObjects.size(); idx++)
	{
		this->gameObjects[idx]->Update(time);
	}

	if (this->playerProjectile->GetModel()->GetPosition().GetY() > 14)
	{
		this->isProjectileActive = true;
	}
	if (this->pressedLeft)
	{
		this->player->Action("LEFT");
	}
	if (this->pressedRight)
	{
		this->player->Action("RIGHT");
	}
	ImpactAlien();
	ImpactPlayer();
	AlienMovement();
	timer++;
	if (timer % 120 == 0)
		Shoot_Alien();
	this->RemoveGameObject(this->pointsText);
	this->pointsText = new Text(Vector3D(-3, 10, 6.5), "Points: " + std::to_string(points));
	this->AddGameObject(this->pointsText);
	this->RemoveGameObject(this->livesText);
	this->livesText = new Text(Vector3D(11.5, 10, 6.5), "Lives: " + std::to_string(this->player->GetLives()));
	this->AddGameObject(this->livesText);
	
}

void MainScene::ProcessKeyPressed(unsigned char key, int px, int py)
{
	if (key == 'a' || key == 'A')
	{
		this->pressedLeft = true;
	}
	if (key == 'd' || key == 'D')
	{
		this->pressedRight = true;
	}
	if ((key == ' ' || key == 'w' || key == 'W') && this->isProjectileActive == true)
	{
		this->isProjectileActive = false;
		this->playerProjectile->ShootProjectile(this->player->GetPosX(), this->player->GetPosY());
	}
}

void MainScene::ProcessKeyReleased(unsigned char key, int px, int py)
{
	if (key == 'a' || key == 'A')
	{
		this->pressedLeft = false;
	}
	if (key == 'd' || key == 'D')
	{
		this->pressedRight = false;
	}
}

void MainScene::ProcessKeyArrows(unsigned char key, int px, int py)
{
	if (key == GLUT_KEY_LEFT)
	{
		this->pressedLeft = true;
	}
	if (key == GLUT_KEY_RIGHT)
	{
		this->pressedRight = true;
	}
}

void MainScene::ProcessKeyArrowsUp(unsigned char key, int px, int py)
{
	if (key == GLUT_KEY_LEFT)
	{
		this->pressedLeft = false;
	}
	if (key == GLUT_KEY_RIGHT)
	{
		this->pressedRight = false;
	}
}

void MainScene::RestartMainScene()
{
	this->RemoveGameObject(this->enemyProjectile->GetModel());
	this->RemoveGameObject(this->playerProjectile->GetModel());
	this->RemoveGameObject(this->player->GetPlayer());
	this->player->SetLives(2);
	this->isProjectileActive = true;
	this->pressedLeft = false;
	this->pressedRight = false;
	
	for (int i = 0; i < 33; ++i)
	{
		this->RemoveGameObject(this->enemies[i]->GetEnemy());
	}
	this->enemies.clear();
	this->Init();
}

void MainScene::ImpactAlien()
{
	int killCount = 0;
	for (int i = 0; i < 33; i++) {
		if (this->playerProjectile->GetModel()->GetPosition().GetY() > this->enemies[i]->GetEnemy()->GetPosition().GetY() - 0.5
			&& this->playerProjectile->GetModel()->GetPosition().GetY() < this->enemies[i]->GetEnemy()->GetPosition().GetY() + 0.5
			&& this->playerProjectile->GetModel()->GetPosition().GetX() > this->enemies[i]->GetEnemy()->GetPosition().GetX() - 0.5
			&& this->playerProjectile->GetModel()->GetPosition().GetX() < this->enemies[i]->GetEnemy()->GetPosition().GetX() + 0.5
			&& this->enemies[i]->GetState() == true)
		{
			this->isProjectileActive = true;
			this->enemies[i]->SetState(false);
			this->playerProjectile->GetModel()->SetPosition(Vector3D(0, -100, 0));
			this->playerProjectile->GetModel()->SetSpeed(Vector3D(0, 0, 0));
			this->RemoveGameObject(this->enemies[i]->GetEnemy());
			this->points += 20;

		}
		if (this->enemies[i]->GetState() == false)
		{
			killCount++;
		}
	}
	
	if (killCount == 33)
	{
		this->gameSpeed += 0.05;
		RestartMainScene();
	}
}

void MainScene::AlienMovement()
{
	for (int i = 0; i < 33; i++) {
		if ((this->enemies[i]->GetEnemy()->GetPosition().GetX() >= 16 || this->enemies[i]->GetEnemy()->GetPosition().GetX() <= -6)
			&& this->enemies[i]->GetState() == true)
		{
			this->changeDir = true;
		}
		if (this->enemies[i]->GetEnemy()->GetPosition().GetY() - 0.5 <= this->player->GetPlayer()->GetPosition().GetY() + 1 && this->enemies[i]->GetState() == true)
		{
			gameOver = true;
		}
	}

	if (this->changeDir == true)
	{
		this->changeDir = false;
		for (int i = 0; i < 33; i++)
		{
			this->enemies[i]->GetEnemy()->SetPosition(Vector3D(this->enemies[i]->GetEnemy()->GetPosition().GetX(), this->enemies[i]->GetEnemy()->GetPosition().GetY() - 0.5, 0.0));
			this->enemies[i]->GetEnemy()->SetSpeed(Vector3D(this->enemies[i]->GetEnemy()->GetSpeed().GetX() * -1, 0.0, 0.0));
		}
	}
}

void MainScene::Shoot_Alien()
{
	int randInt;
	do
	{
		randInt = rand() % 33;
	} while (this->enemies[randInt]->GetState() == false);

	this->enemyProjectile->ShootProjectile(this->enemies[randInt]->GetEnemy()->GetPosition().GetX(), this->enemies[randInt]->GetEnemy()->GetPosition().GetY());
}

void MainScene::ImpactPlayer()
{
	if (this->enemyProjectile->GetModel()->GetPosition().GetY() > this->player->GetPlayer()->GetPosition().GetY() - 1
		&& this->enemyProjectile->GetModel()->GetPosition().GetY() < this->player->GetPlayer()->GetPosition().GetY() + 1
		&& this->enemyProjectile->GetModel()->GetPosition().GetX() > this->player->GetPlayer()->GetPosition().GetX() - 1
		&& this->enemyProjectile->GetModel()->GetPosition().GetX() < this->player->GetPlayer()->GetPosition().GetX() + 1)
	{
		this->enemyProjectile->GetModel()->SetPosition(Vector3D(0.0, -10.0, 0.0));
		this->player->SetLives(this->player->GetLives() - 1);
		if (this->player->GetLives() <= 0)
			gameOver = true;
	}
}

int MainScene::GetNextScene()
{
	if (!gameOver) return 0;
	else
	{
		gameOver = false;
		this->gameSpeed = 0.05;
		points = 0;
		RestartMainScene();
		return 1;
	}
}
