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

#include "CEngine.hpp"
#include "CPhysics.hpp"
#include "CEventReceiver.hpp"
#include "CDebugDraw.hpp"

CEngine engine;

CEngine::CEngine()
{

}

CEngine::~CEngine()
{

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
	_debugDraw = new CDebugDraw(_device);
	_debugDraw->setDebugMode(
			btIDebugDraw::DBG_DrawWireframe |
			btIDebugDraw::DBG_DrawAabb |
			btIDebugDraw::DBG_DrawContactPoints |
			//btIDebugDraw::DBG_DrawText |
			//btIDebugDraw::DBG_DrawConstraintLimits |
			btIDebugDraw::DBG_DrawConstraints);
	_physics->SetDebugDraw(_debugDraw);

	_receiver.SetIrrDevice(_device);
}

void CEngine::CleanUp()
{
	_physics->CleanUp();
	if(_device)
		_device->drop();
	delete _physics;
	delete _debugDraw;
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

CEventReceiver* CEngine::GetEventReceiver()
{
	return &_receiver;
}
