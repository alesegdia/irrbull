#ifndef __CEVENTRECEIVER__
#define __CEVENTRECEIVER__

#include "common.h"

class CEventReceiver : public IEventReceiver
{
public:

	CEventReceiver();
	~CEventReceiver();

	void SetEngine(CEngine* engine);
	virtual bool OnEvent(const SEvent& event);
	virtual bool IsKeyDown (EKEY_CODE keyCode) const;
	s32 GetDeltaMouseX();
	void SetIrrDevice(IrrlichtDevice* device);

	core::position2di mousePos;

private:
	bool KeyIsDown[KEY_KEY_CODES_COUNT];
	IrrlichtDevice* _device;
	s32 _deltaMouseX;
};

#endif
