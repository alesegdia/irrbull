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

#include "CGame.hpp"
#include "CEngine.hpp"
#include "CPhysics.hpp"
#include "CEventReceiver.hpp"
#include "CGameObjectManager.hpp"
#include "GOEntity.hpp"
#include "GOEntityController.hpp"

CGame::CGame()
{

}

CGame::~CGame()
{
	delete _engine;
}

void CGame::Init()
{
	_engine = new CEngine();
	_engine->Init();
	_goMgr = new CGameObjectManager();
	_goMgr->SetEngine(_engine);
}

btRigidBody* CGame::PushSphere(const btVector3& position, f32 radius, btScalar mass)
{
	scene::ISceneNode* _cube = _engine->GetSMgr()->addSphereSceneNode(radius);
	_cube->setMaterialFlag(video::EMF_LIGHTING,1);
	_cube->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);

	btRigidBody* rb = _engine->GetPhysics()->PushObject(
			position,
			core::vector3df(1,1,1),
			new btSphereShape(radius),
			mass);
	rb->setUserPointer((void*)_cube);
	return rb;
}

btRigidBody* CGame::PushCube(const btVector3& position, const core::vector3df& scale, btScalar mass)
{
	scene::ISceneNode* _cube = _engine->GetSMgr()->addCubeSceneNode(1.f);
	_cube->setScale(scale);
	_cube->setMaterialFlag(video::EMF_LIGHTING,1);
	_cube->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);

	btRigidBody* rb = _engine->GetPhysics()->PushObject(
			position,
			scale,
			new btBoxShape(btVector3(scale.X/2, scale.Y/2, scale.Z/2)),
			mass);
	rb->setUserPointer((void*)_cube);
	return rb;
}

void CGame::SetupScene()
{
	/* LIGHTS ON! **************************/
	_light1 =
		_engine->GetSMgr()->addLightSceneNode(
				0, core::vector3df(1000,1000,0),
				video::SColorf(0.3f,0.3f,0.3f),
				1000.f, 1);
	if(_light1)
	{
		_light1->getLightData().Attenuation.set(0.f,1.f/4000.f, 0.f);
	}

	/* MAP *********************************/
	std::string mapMeshPath("../media/abarba.obj");
	std::string mapTexturePath("");
	GOEntity* tmpEntity;
	tmpEntity = new GOEntity();
	tmpEntity->Load(
			_engine,
			mapMeshPath,
			mapTexturePath,
			btVector3(0,0,0),
			core::vector3df(1,1,1),
			new btBoxShape(btVector3(500.f, 1.f, 500.f)));
	_goMgr->RegisterGameObject(tmpEntity, "map");
	//_entities.push_back(tmpEntity);

	/* PLAYER ******************************/
	std::string playerMesh("../media/doom/Cyberdemon/Cyber.md2");
	std::string playerTexture("../media/doom/Cyberdemon/cyber.jpg");

	tmpEntity = new GOEntity();
	btCollisionShape* capsuleShape = new btCapsuleShape(10.f, 20.f);
	btCompoundShape* compound = new btCompoundShape();
	btTransform localTrans;
	localTrans.setIdentity();
	localTrans.setOrigin(btVector3(0,14,0));
	compound->addChildShape(localTrans,capsuleShape);
	btVector3 v3(0.f, 300.f, 0.f);

	tmpEntity->Load(
			_engine,
			playerMesh,
			playerTexture,
			v3, //btVector3(0.f, 300.f, 0.f),
			core::vector3df(0.125f,0.125f,0.125f),
			compound, //new btCapsuleShape(10.f, 20.f),
			btScalar(10));
	tmpEntity->GetNode()->setAnimationSpeed(70);
	tmpEntity->GetNode()->setFrameLoop(22,22);
	tmpEntity->GetNode()->setLoopMode(true);
	tmpEntity->GetRigidBody()->setAngularFactor(btVector3(0,0,0));
	_goMgr->RegisterGameObject(tmpEntity, "player");
	//_entities.push_back(tmpEntity);
/* 
	btVector3 v1(100,200,0);
	PushSphere(
		v1,
		10,
		50);
*/
	PushSphere(
		btVector3(100,300,0),
		10,
		50);

	PushSphere(
		btVector3(100,400,0),
		10,
		50);

	PushSphere(
		btVector3(100,500,0),
		10,
		50);

	PushCube(
		btVector3(0,100,0),
		core::vector3df(10,10,10),
		10);

	/* PLAYER CONTROLLER *******************/
	IGameObject* entityController = new GOEntityController(_engine);
	(static_cast<GOEntityController*>(entityController))->AttachEntity(tmpEntity);
	_goMgr->RegisterGameObject(tmpEntity, "playercontroller");
	//_gameObjects.push_back(entityController);

	/* CAMARA ******************************/
	_camNode = _engine->GetSMgr()->addCameraSceneNode();
	(_goMgr->GetGameObjectByTag<GOEntity>("player"))->AttachCamera(_camNode,
			core::vector3df(-500,250,0));
			//core::vector3df(-400,200,-200));

}

void CGame::Start()
{
	/*
	for(auto it = _gameObjects.begin(); it != _gameObjects.end(); it++)
	{
		(*it).Start();
	}
	*/
}

void CGame::Update()
{
	/*
	for(auto it = _gameObjects.begin(); it != _gameObjects.end(); it++)
	{
		(*it).Update();
	}
	*/
}

void CGame::Run()
{
	Init();
	SetupScene();
	_goMgr->Awake();
	_goMgr->Start();
	//Start();


	irr::video::SMaterial debugMat;
	debugMat.Lighting = false;

	// _engine->Update()?
	u32 then = _engine->GetIrrDevice()->getTimer()->getTime();
	while(_engine->IsRunning())
	{
		// _engine->DrawAll()??
		if(_engine->GetIrrDevice()->isWindowActive())
		{
			/* RENDERING */
			_engine->GetVideoDriver()->beginScene(true, true, video::SColor(64, 67, 74, 255));
			_engine->GetSMgr()->drawAll();

			_engine->GetVideoDriver()->setMaterial(debugMat);
			_engine->GetVideoDriver()->setTransform(irr::video::ETS_WORLD, irr::core::IdentityMatrix);
			_engine->GetPhysics()->DebugDrawWorld();
			_engine->GetVideoDriver()->endScene();
		}
		else
		{
			_engine->GetIrrDevice()->yield();
		}

		const u32 now = _engine->GetIrrDevice()->getTimer()->getTime();
		u32 delta = (now-then);
		then = now;
		_engine->GetPhysics()->UpdatePhysics(delta);

		_goMgr->Update();
		//Update();
		PlaceCamera();

		//_engine->GetIrrDevice()->getCursorControl()->setPosition(100,100);
		//Update();

	}
	_goMgr->Unload();
	std::cout << "\nolaqase\n";
	_engine->CleanUp();
	std::cout << "\ncuentameloqase\n";
}

// camera->attachTo(PlayerNode);
// camera->update();
void CGame::PlaceCamera()
{
	GOEntity *target = _goMgr->GetGameObjectByTag<GOEntity>("player");
	btTransform xform;
	target->GetRigidBody()->getMotionState()->getWorldTransform(xform);
	btVector3 forward = xform.getBasis()[2];
	forward.normalize();

	f32 factor = 25;
	_camNode->setTarget(target->GetNode()->getPosition());
	//_camNode->setTarget(
	//		_entities[1].GetNode()->getPosition()
	//		+ core::vector3df(
	//			forward.getZ()*factor,20,forward.getX()*factor));
}
