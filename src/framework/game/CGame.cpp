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

#include "framework/game/IScreen.hpp"
#include "framework/game/CGame.hpp"
#include "framework/CEngine.hpp"
#include "framework/physics/CPhysics.hpp"
#include "framework/input/CEventReceiver.hpp"
#include "framework/game/gameobject/CGameObjectManager.hpp"
#include "game/test/gameobject/GOEntity.hpp"
#include "game/test/gameobject/GOEntityController.hpp"
#include "game/test/gameobject/GOCamera.hpp"
#include "game/test/gameobject/GOIAController.hpp"

CGame::CGame()
{

}

CGame::~CGame()
{

}

void CGame::Init()
{	engine.Init();
	_goMgr = new CGameObjectManager();
}

btRigidBody* CGame::PushSphere(const btVector3& position, f32 radius, btScalar mass)
{
	scene::ISceneNode* _cube = engine.GetSMgr()->addSphereSceneNode(radius);
	_cube->setMaterialFlag(video::EMF_LIGHTING,1);
	_cube->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);

	btRigidBody* rb = engine.GetPhysics()->PushObject(
			position,
			core::vector3df(1,1,1),
			new btSphereShape(radius),
			mass);
	rb->setUserPointer((void*)_cube);
	return rb;
}

btRigidBody* CGame::PushCube(const btVector3& position, const core::vector3df& scale, btScalar mass)
{
	scene::ISceneNode* _cube = engine.GetSMgr()->addCubeSceneNode(1.f);
	_cube->setScale(scale);
	_cube->setMaterialFlag(video::EMF_LIGHTING,1);
	_cube->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);

	btRigidBody* rb = engine.GetPhysics()->PushObject(
			position,
			scale,
			new btBoxShape(btVector3(scale.X/2, scale.Y/2, scale.Z/2)),
			mass);
	rb->setUserPointer((void*)_cube);
	return rb;
}





void CGame::SetupScene()
{
}


void CGame::Run()
{
	IScreen::game = this;
	Init();
	currentScreen->Awake();
	_goMgr->Awake();
	currentScreen->ConnectSlots();
	_goMgr->Start();

	irr::video::SMaterial debugMat;
	debugMat.Lighting = false;
	bool pause = false;

	// engine.Update()?
	u32 then = engine.GetIrrDevice()->getTimer()->getTime();
	engine.GetIrrDevice()->getCursorControl()->setVisible(false);
	while(engine.IsRunning())
	{
		// engine.DrawAll()??
		if(engine.GetIrrDevice()->isWindowActive())
		{
			/* RENDERING */
			engine.GetVideoDriver()->beginScene(true, true, video::SColor(64, 67, 74, 255));
			engine.GetSMgr()->drawAll();

			engine.GetVideoDriver()->setMaterial(debugMat);
			engine.GetVideoDriver()->setTransform(irr::video::ETS_WORLD, irr::core::IdentityMatrix);
			engine.GetPhysics()->DebugDrawWorld();
			engine.GetVideoDriver()->endScene();
		}
		else
		{
			engine.GetIrrDevice()->yield();
		}

		const u32 now = engine.GetIrrDevice()->getTimer()->getTime();
		u32 delta = (now-then);
		then = now;
		if(!pause) engine.GetPhysics()->UpdatePhysics(delta);

		if(engine.GetEventReceiver()->IsKeyDown(KEY_KEY_P))
		{
			pause = !pause;
			//engine.GetPhysics()->pause();
			//engine.GetPhysics()->DeleteEntity(_goMgr->GetGameObjectByTag<GOEntity>("map"));
		}

		_goMgr->Update();
	}

	_goMgr->Unload();
	_goMgr->FreeEverything();
	engine.CleanUp();
}
