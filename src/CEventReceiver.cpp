#include "CEventReceiver.hpp"

CEventReceiver::CEventReceiver()
{
	for(u32 i=0; i<KEY_KEY_CODES_COUNT; i++)
	{
		KeyIsDown[i] = false;
	}
}

CEventReceiver::~CEventReceiver()
{

}

bool CEventReceiver::OnEvent(const SEvent& event)
{
	if(event.EventType == irr::EET_KEY_INPUT_EVENT)
	{
		KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
	}
	else if(event.EventType == irr::EET_MOUSE_INPUT_EVENT)
	{
		if(event.MouseInput.Event == EMIE_MOUSE_MOVED)
		{
			mousePos.X = event.MouseInput.X;
			mousePos.Y = event.MouseInput.Y;
			//_device->getCursorControl()->setPosition(100,100);
		}
	}
}

bool CEventReceiver::IsKeyDown(EKEY_CODE keyCode) const
{
	return KeyIsDown[keyCode];
}

void CEventReceiver::SetIrrDevice(IrrlichtDevice* device)
{
	_device = device;
}

s32 CEventReceiver::GetDeltaMouseX()
{
	return _deltaMouseX;
}
