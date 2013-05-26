#ifndef __CEVENTRECEIVER__
#define __CEVENTRECEIVER__

#include "common.h"

class CEventReceiver : public IEventReceiver
{
public:

	core::position2di mousePos;

	CEventReceiver ()
	{
		for(u32 i=0; i<KEY_KEY_CODES_COUNT; i++)
			KeyIsDown[i] = false;
	}

	virtual bool OnEvent(const SEvent& event)
	{
		if(event.EventType == irr::EET_KEY_INPUT_EVENT)
			KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
		else if(event.EventType == irr::EET_MOUSE_INPUT_EVENT)
		{
			if (event.MouseInput.Event == EMIE_MOUSE_MOVED)
			{
				mousePos.X = event.MouseInput.X;
				mousePos.Y = event.MouseInput.Y;
			}
		}
		return false;
	}

	virtual bool IsKeyDown (EKEY_CODE keyCode) const
	{
		return KeyIsDown[keyCode];
	}

private:
	bool KeyIsDown[KEY_KEY_CODES_COUNT];
};

#endif
