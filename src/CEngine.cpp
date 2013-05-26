#include "CEngine.hpp"
#include "CPhysics.hpp"
#include "CEventReceiver.hpp"

CEngine::CEngine()
{

}

CEngine::~CEngine()
{
	if(_device)
		_device->drop();
}

void CEngine::Init(int wWidth, int wHeight)
{
	_device = createDevice(
			video::EDT_OPENGL, core::dimension2d<u32>(wWidth, wHeight),
			16, false, false, false, &_receiver);

	if(!_device)
		exit(EXIT_FAILURE);

	_driver = _device->getVideoDriver();
	_smgr = _device->getSceneManager();
	_physics = new CPhysics();
	_physics->Init(WORLD_GRAVITY);
}

bool CEngine::IsRunning() const
{
	return _device->run();
}

bool CEngine::IsKeyDown(EKEY_CODE keyCode) const
{
	return _receiver.IsKeyDown(keyCode);
}

scene::ISceneManager* CEngine::GetSMgr()
{
	return _smgr;
}

IrrlichtDevice* CEngine::GetIrrDevice()
{
	return _device;
}

CPhysics* CEngine::GetPhysics()
{
	return _physics;
}

video::IVideoDriver* CEngine::GetVideoDriver()
{
	return _driver;
}
