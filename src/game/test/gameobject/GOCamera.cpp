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

#include "GOCamera.hpp"
#include "framework/CEngine.hpp"

GOCamera::GOCamera()
{

}

GOCamera::~GOCamera()
{

}

void GOCamera::LookAt(const core::vector3df& v)
{
	_cam->setTarget(v);
}

scene::ISceneNode* GOCamera::GetNode()
{
	return _cam;
}

void GOCamera::Awake()
{
	_cam = engine.GetSMgr()->addCameraSceneNode();
}

void GOCamera::Start()
{

}

void GOCamera::Update()
{

}

void GOCamera::Unload()
{

}

