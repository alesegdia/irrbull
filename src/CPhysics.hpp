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

#ifndef __CPHYSICS__
#define __CPHYSICS__

#include "common.h"
#include "CDebugDraw.hpp"

class CPhysics
{
public:
	CPhysics();
	~CPhysics();

	void Init(btScalar gravity);
	void CleanUp();
	void UpdatePhysics (u32 delta);
	btRigidBody* PushObject(
			//scene::ISceneNode* node,
			const btVector3& position,
			const core::vector3df& scale,
			btCollisionShape* colShape = NULL,
			btScalar mass = 0.f);
	void ClearObjects();
	void SetDebugDraw(CDebugDraw* debugDraw);
	void DebugDrawWorld();
	btDiscreteDynamicsWorld* GetWorld();

private:
	void UpdateRender(btRigidBody* obj);

	std::vector<btRigidBody*> _bodies;
	boost::ptr_vector<btCollisionShape> _shapes;

	/* Bullet stuff */
	btDiscreteDynamicsWorld* _world;
	btDefaultCollisionConfiguration *CollisionConfiguration;
	btBroadphaseInterface *BroadPhase;
	btCollisionDispatcher *Dispatcher;
	btSequentialImpulseConstraintSolver *Solver;
};

#endif
