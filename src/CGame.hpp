//	IrrBull is a very simple engine integrating Irrlicht and Bullet.
//	Copyright (C) 2013 Alejandro Seguí Díaz <alesegdia at gmail dot com>
//
//	IrrBull is free software: you can redistribute it and/or modify
//	it under the terms of the GNU General Public License as published by
//	the Free Software Foundation, either version 3 of the License, or
//	(at your option) any later version.
//
//	IrrBull is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//	GNU General Public License for more details.
//
//	You should have received a copy of the GNU General Public License
//	along with IrrBull.  If not, see <http://www.gnu.org/licenses/>.

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
	btRigidBody* PushSphere(
			const core::vector3df& position,
			f32 radius,
			btScalar mass);

	btRigidBody* PushCube(
			const core::vector3df& position,
			const core::vector3df& scale,
			btScalar mass);

private:
	CEngine* _engine;
	scene::ICameraSceneNode* _camNode;
	scene::ILightSceneNode* _light1;
	boost::ptr_vector<CEntity> _entities;
	boost::ptr_vector<IGameObject> _gameObjects;
};

#endif
