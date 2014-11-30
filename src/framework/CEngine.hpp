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

#ifndef __CENGINE__
#define __CENGINE__

#include "framework/common.h"

// porque sino no cuela, para hacer el forward declaring,
// tiene que ser un puntero, sino necesita inicializacion en este file.
#include "framework/input/CEventReceiver.hpp"
#include "framework/physics/CDebugDraw.hpp"

class CEngine
{
public:
	CEngine();
	~CEngine();

	void Init(int wWidth=800, int wHeight=600);
	bool IsKeyDown(EKEY_CODE keyCode) const;
	bool IsRunning() const;
	scene::ISceneManager* GetSMgr();
	video::IVideoDriver* GetVideoDriver();
	IrrlichtDevice* GetIrrDevice();
	CEventReceiver* GetEventReceiver();
	CPhysics* GetPhysics();
	void CleanUp();

private:
	IrrlichtDevice* _device;
	video::IVideoDriver* _driver;
	CEventReceiver _receiver;
	CDebugDraw* _debugDraw;
	CPhysics* _physics;
	scene::ISceneManager* _smgr;
};

extern CEngine engine;
#endif
