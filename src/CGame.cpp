#include "CGame.hpp"
#include "CEntity.hpp"
#include "CEngine.hpp"
#include "CPhysics.hpp"

CGame::CGame()
{

}

CGame::~CGame()
{

}

void CGame::Init()
{
	_engine = new CEngine();
	_engine->Init();
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
	CEntity* tmpEntity;
	tmpEntity = new CEntity();
	tmpEntity->Load(
			_engine,
			mapMeshPath,
			mapTexturePath,
			btVector3(0,0,0),
			core::vector3df(1,1,1),
			new btBoxShape(btVector3(100.f, 1.f, 100.f)));
	_entities.push_back(tmpEntity);

	/* PLAYER ******************************/
	std::string playerMesh("../media/doom/Cyberdemon/Cyber.md2");
	std::string playerTexture("../media/doom/Cyberdemon/cyber.jpg");

	tmpEntity = new CEntity();
	btCollisionShape* capsuleShape = new btCapsuleShape(10.f, 20.f);
	btCompoundShape* compound = new btCompoundShape();
	btTransform localTrans;
	localTrans.setIdentity();
	localTrans.setOrigin(btVector3(0,14,0));
	compound->addChildShape(localTrans,capsuleShape);

	tmpEntity->Load(
			_engine,
			playerMesh,
			playerTexture,
			btVector3(0.f, 1000.f, 0.f),
			core::vector3df(0.125f,0.125f,0.125f),
			compound, //new btCapsuleShape(10.f, 20.f),
			btScalar(10));
	tmpEntity->GetNode()->setAnimationSpeed(70);
	tmpEntity->GetNode()->setFrameLoop(22,22);
	tmpEntity->GetNode()->setLoopMode(true);
	_entities.push_back(tmpEntity);

	/* CAMARA ******************************/
	_camNode = _engine->GetSMgr()->addCameraSceneNode();
	_entities[1].AttachCamera(_camNode,
			core::vector3df(-500,300,0));

}

void CGame::Update()
{
	for(auto it = _entities.begin(); it != _entities.end(); it++)
	{
		//(*it).Update();
	}
}

void CGame::Run()
{
	Init();
	SetupScene();

	irr::video::SMaterial debugMat;
	debugMat.Lighting = false;

	u32 then = _engine->GetIrrDevice()->getTimer()->getTime();
	while(_engine->IsRunning())
	{
		const u32 now = _engine->GetIrrDevice()->getTimer()->getTime();
		const u32 delta = (now-then);
		then = now;

		_engine->GetPhysics()->UpdatePhysics(delta);
		PlaceCamera();

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
	}
}

// camera->attachTo(PlayerNode);
// camera->update();
void CGame::PlaceCamera()
{
	_camNode->setTarget(_entities[1].GetNode()->getPosition());
}
