#pragma once
#include <vector>
#include "Camera.h"
#include "ModelLoader.h"
#include "Model.h"
#include "Text.h"

class Scene
{
protected:

	Camera camera;
	vector<Solid*> gameObjects;


public:
	Scene() {};

	inline void AddGameObject(Solid* gameObject) { this->gameObjects.push_back(gameObject); }

	inline void RemoveGameObject(Solid* gameObject) 
	{
		auto objectToRemove = std::find(gameObjects.begin(), gameObjects.end(), gameObject);
		if (objectToRemove != gameObjects.end()) 
		{
			gameObjects.erase(objectToRemove);
		}
	}

	virtual void Init() = 0;
	virtual void Render() = 0;
	virtual void Update(const float& time, int& puntos) = 0;
	virtual void ProcessKeyPressed(unsigned char key, int px, int py) = 0;
	virtual void ProcessKeyReleased(unsigned char key, int px, int py) = 0;
	virtual void ProcessKeyArrows(unsigned char key, int px, int py) = 0;
	virtual void ProcessKeyArrowsUp(unsigned char key, int px, int py) = 0;
	virtual int GetNextScene() = 0;							
};

