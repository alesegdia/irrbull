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

#include "framework/common.h"

class IScreen;

class CGame
{
public:
	CGame();
	~CGame();

	void SetScreen( IScreen* screen )
	{
		currentScreen = screen;
	}

	void Init();
	void SetupScene();
	void ConnectSlots();
	void Run();
	void DebugDrawWorld();
	btRigidBody* PushSphere(
			const btVector3& position,
			f32 radius,
			btScalar mass);

	btRigidBody* PushCube(
			const btVector3& position,
			const core::vector3df& scale,
			btScalar mass);
	CGameObjectManager *_goMgr;

private:
	IScreen* currentScreen;
	scene::ICameraSceneNode* _camNode;
	scene::ILightSceneNode* _light1;
};

#endif
