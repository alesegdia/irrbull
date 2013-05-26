#ifndef __CENGINE__
#define __CENGINE__

#include "common.h"

// porque sino no cuela, para hacer el forward declaring,
// tiene que ser un puntero, sino necesita inicializacion en este file.
#include "CEventReceiver.hpp"

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
	CPhysics* GetPhysics();

private:
	IrrlichtDevice* _device;
	video::IVideoDriver* _driver;
	CEventReceiver _receiver;
	CPhysics* _physics;
	scene::ISceneManager* _smgr;
};


#endif
