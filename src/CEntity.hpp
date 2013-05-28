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

#ifndef __CENTITY__
#define __CENTITY__

#include "common.h"

class CEntity : public IGameObject
{
public:
	CEntity();
	virtual ~CEntity();

	void Load(
			CEngine* engine,
			const std::string& meshPath,
			const std::string& texturePath,
			const btVector3& position=btVector3(0,0,0),
			const core::vector3df& scale=core::vector3df(1,1,1),
			btCollisionShape* shape=NULL,
			btScalar  mass=0);
	scene::IAnimatedMeshSceneNode* GetNode();
	void AttachCamera(scene::ICameraSceneNode* camNode,
			const core::vector3df& position);
	btRigidBody* GetRigidBody();

	/* GAMEOBJECT INTERFACE */
	void Start();
	void Update();

protected:
	scene::IAnimatedMesh *_mesh;
	scene::IAnimatedMeshSceneNode* _node;
	btRigidBody* _rigidBody;
};


#endif
