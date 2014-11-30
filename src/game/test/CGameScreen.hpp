
#pragma once

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

class CGameScreen : public IScreen
{
private:

	btRigidBody* PushSphere(const btVector3& position, f32 radius, btScalar mass)
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

	btRigidBody* PushCube(const btVector3& position, const core::vector3df& scale, btScalar mass)
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

	void Awake()
	{
	/* LIGHTS ON! **************************/
	_light1 =
		engine.GetSMgr()->addLightSceneNode(
				0, core::vector3df(1000,1000,0),
				video::SColorf(0.3f,0.3f,0.3f),
				1000.f, 1);
	if(_light1)
	{
		_light1->getLightData().Attenuation.set(0.f,1.f/4000.f, 0.f);
	}


	/* MAP *********************************/
	GOEntity* tmp;
	tmp = new GOEntity();

	tmp->Load("../media/abarba.3ds", "",
			btVector3(0,0,300), core::vector3df(1,1,1),
			NULL);//new btBoxShape(btVector3(500.f, 1.f, 500.f)));
	game->_goMgr->RegisterGameObject(tmp, "map");


	/* PLAYER ******************************/
	tmp = new GOEntity();
	btCollisionShape* capsuleShape = new btCapsuleShape(10.f, 20.f);
	btCompoundShape* compound = new btCompoundShape();
	btTransform localTrans;
	localTrans.setIdentity();
	localTrans.setOrigin(btVector3(0,14,0));
	compound->addChildShape(localTrans,capsuleShape);
	tmp->Load("../media/doom/Cyberdemon/Cyber.md2",
			"../media/doom/Cyberdemon/cyber.jpg",
			btVector3(0.f, 300.f, 100.f),
			core::vector3df(0.11f,0.11f,0.11f),
			compound, btScalar(10));
	tmp->GetNode()->setAnimationSpeed(70);
	tmp->GetNode()->setFrameLoop(22,22);
	tmp->GetNode()->setLoopMode(true);
	tmp->GetRigidBody()->setAngularFactor(btVector3(0,0,0));
	game->_goMgr->RegisterGameObject(tmp, "player");


	/* ENEMY ******************************/
	tmp = new GOEntity();
	btCollisionShape* capsuleShape2 = new btCapsuleShape(10.f, 20.f);
	btCompoundShape* compound2 = new btCompoundShape();
	btTransform localTrans2;
	localTrans2.setIdentity();
	localTrans2.setOrigin(btVector3(0,14,0));
	compound2->addChildShape(localTrans2,capsuleShape2);
	tmp->Load("../media/revenant/Revenant.md2",
			"../media/revenant/revenant.jpg",
			btVector3(0.f, 300.f, 0.f),
			core::vector3df(0.50f,0.50f,0.50f),
			compound2, btScalar(10));
	tmp->GetNode()->setAnimationSpeed(40);
	tmp->GetNode()->setFrameLoop(12,35);
	tmp->GetNode()->setLoopMode(true);
	tmp->GetRigidBody()->setAngularFactor(btVector3(0,0,0));
	game->_goMgr->RegisterGameObject(tmp, "enemy");

	/* IA CONTROLLER *************************/
    GOIAController* iacont = new GOIAController();
    game->_goMgr->RegisterGameObject(iacont, "iacontroller");


	/* PLAY OBJECTS **************************/
	PushSphere(
		btVector3(100,200,0),
		10,
		50);

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

	PushCube(
		btVector3(0,0,150),
		core::vector3df(500,5,500),
		0);

	/* PLAYER CONTROLLER *******************/
	IGameObject* entityController = new GOEntityController();
	game->_goMgr->RegisterGameObject(entityController, "playercontroller");


	/* CAMARA ******************************/
	IGameObject* camera = new GOCamera();
	game->_goMgr->RegisterGameObject(camera, "maincamera");
		
	}

	void ConnectSlots()
	{
		GOCamera* cam =                  game->_goMgr->GetGameObjectByTag<GOCamera>          ("maincamera");
		GOEntityController* controller = game->_goMgr->GetGameObjectByTag<GOEntityController>("playercontroller");
		GOEntity* entity =               game->_goMgr->GetGameObjectByTag<GOEntity>          ("player");
		GOIAController* iacont =         game->_goMgr->GetGameObjectByTag<GOIAController>    ("iacontroller");
		GOEntity* enemy =                game->_goMgr->GetGameObjectByTag<GOEntity>          ("enemy");

		controller->AttachCamera(cam);
		controller->AttachEntity(entity);
		iacont->SetPlayer(entity);
		iacont->SetEntity(enemy);
	}
	scene::ILightSceneNode* _light1;

public:
};
