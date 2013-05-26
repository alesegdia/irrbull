#ifndef __GAME__
#define __GAME__

#include "common.h"

class CGame
{
public:
	CGame();
	~CGame();

	void Init();
	void SetupScene();
	void Start();
	void Update();
	void Run();
	void PlaceCamera();
	void DebugDrawWorld();

private:
	CEngine* _engine;
	scene::ICameraSceneNode* _camNode;
	scene::ILightSceneNode* _light1;
	boost::ptr_vector<CEntity> _entities;
	boost::ptr_vector<IGameObject> _gameObjects;
};

#endif
