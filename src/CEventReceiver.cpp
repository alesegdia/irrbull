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
