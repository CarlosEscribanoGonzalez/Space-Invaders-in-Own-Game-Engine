#pragma once
#include "Scene.h"

class GameOverScene : public Scene
{
private:
	int points;
	bool restart;
	Text* gameOverText;
	Text* restartInfo;
	Text* finalPointsText;

public:
	GameOverScene() : restart(false) {}
	void Init();
	void Render();
	void Update(const float& time, int& puntos);
	void ProcessKeyPressed(unsigned char key, int px, int py);
	void ProcessKeyReleased(unsigned char key, int px, int py) {};
	void ProcessKeyArrows(unsigned char key, int px, int py) {};
	void ProcessKeyArrowsUp(unsigned char key, int px, int py) {};
	int GetNextScene();
};

