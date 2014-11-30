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

#include "GOEntity.hpp"
#include "framework/CEngine.hpp"
#include "framework/physics/CPhysics.hpp"

GOEntity::GOEntity()
{

}

GOEntity::~GOEntity()
{

}

btTriangleMesh* IrrMeshToBullet (scene::IMesh *mesh)
{
	btTriangleMesh* tmesh = new btTriangleMesh;
	scene::IMeshBuffer* meshbuffer;
	btVector3 v1, v2, v3;
	btScalar x, y, z;
	int count = 0;
	int cnt = 0;
	for(int i = 0; i < mesh->getMeshBufferCount(); i++)
	{
		meshbuffer = mesh->getMeshBuffer(i);
		u16* indices = meshbuffer->getIndices();
		count = 0;
		for(int j=0; j<meshbuffer->getVertexCount(); j++)
		{
			const core::vector3df v = meshbuffer->getPosition(indices[j]);
			//std::cout << cnt++ << ". " << count << std::endl;
			if(count == 2)
			{
				x=v.X; y=v.Y; z=v.Z;
				v3 = btVector3(x, y, z);
				tmesh->addTriangle(v1, v2, v3);
				count = 0;
			}
			else
			{
				x=v.X; y=v.Y; z=v.Z;
				if(count == 0)
				{
					v1 = btVector3(x,y,z);
				}
				else
				{
					v2 = btVector3(x,y,z);
			    }
			    count++;
			}
		}
	}

	return tmesh;
}

void GOEntity::Load(const std::string& meshPath, const std::string& texturePath,
		const btVector3& position, const core::vector3df& scale,
		btCollisionShape* colShape, btScalar mass)
{
	_mesh = engine.GetSMgr()->getMesh(meshPath.c_str());

	if(!_mesh)
		exit(EXIT_FAILURE);

	video::IVideoDriver* driver = engine.GetVideoDriver();

	_node = engine.GetSMgr()->addAnimatedMeshSceneNode(_mesh);
	_node->setMaterialFlag(irr::video::EMF_LIGHTING, true);

	if(texturePath != "")
		_node->setMaterialTexture(0, driver->getTexture(texturePath.c_str()));

	_node->setScale(scale);

	if(colShape == NULL)
	{
	    scene::IMesh* tmpMesh = engine.GetSMgr()->getMesh(meshPath.c_str());
		btTriangleMesh* tmesh = IrrMeshToBullet(tmpMesh);
		btBvhTriangleMeshShape* tshape = new btBvhTriangleMeshShape(tmesh, true, true);
		_rigidBody = engine.GetPhysics()->PushObject(position, scale, tshape, mass);
	}
	else
	{
	    _rigidBody = engine.GetPhysics()->PushObject(position, scale, colShape, mass);
    }
	_rigidBody->setUserPointer((void*)(_node));
	std::cout << "RigidBody: " << meshPath << ": " << _rigidBody << std::endl;
	std::cout << "NODE: " << _node << std::endl;
}

scene::IAnimatedMeshSceneNode* GOEntity::GetNode()
{
	return _node;
}

btRigidBody* GOEntity::GetRigidBody()
{
	return _rigidBody;
}

void GOEntity::AttachCamera(scene::ICameraSceneNode* camNode, const core::vector3df& position)
{
	camNode->setParent(_node);
	camNode->setPosition(position);
}


void GOEntity::Awake()
{

}

void GOEntity::Start()
{

}

void GOEntity::Update()
{

}

void GOEntity::Unload()
{
	//engine.GetPhysics()->DeleteEntity(this);
}
