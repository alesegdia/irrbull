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

#include "CEntity.hpp"
#include "CEngine.hpp"
#include "CPhysics.hpp"

CEntity::CEntity()
{

}

CEntity::~CEntity()
{
	delete _mesh;
	delete _node;
	delete _rigidBody;
}

void CEntity::Load(CEngine* engine, const std::string& meshPath,
		const std::string& texturePath, const btVector3& position,
		const core::vector3df& scale, btCollisionShape* colShape, btScalar mass)
{
	_mesh = engine->GetSMgr()->getMesh(meshPath.c_str());

	if(!_mesh)
		exit(EXIT_FAILURE);

	video::IVideoDriver* driver = engine->GetVideoDriver();

	_node = engine->GetSMgr()->addAnimatedMeshSceneNode(_mesh);
	_node->setMaterialFlag(irr::video::EMF_LIGHTING, true);

	if(texturePath != "")
		_node->setMaterialTexture(0, driver->getTexture(texturePath.c_str()));

	_node->setScale(scale);

	_rigidBody = engine->GetPhysics()->PushObject(position, scale, colShape, mass);
	_rigidBody->setUserPointer((void*)(_node));
}

scene::IAnimatedMeshSceneNode* CEntity::GetNode()
{
	return _node;
}

btRigidBody* CEntity::GetRigidBody()
{
	return _rigidBody;
}

void CEntity::AttachCamera(scene::ICameraSceneNode* camNode, const core::vector3df& position)
{
	camNode->setParent(_node);
	camNode->setPosition(position);
}

void CEntity::Start()
{

}

void CEntity::Update()
{

}
