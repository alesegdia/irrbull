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

#include "CPhysics.hpp"
#include "CDebugDraw.hpp"
#include "game/test/gameobject/GOEntity.hpp"

CPhysics::CPhysics()
{

}

CPhysics::~CPhysics()
{
}

void CPhysics::Init(btScalar gravity)
{
	CollisionConfiguration = new btDefaultCollisionConfiguration();
	BroadPhase = new btAxisSweep3(
					btVector3(-1000, -1000, -1000),
					btVector3(1000, 1000, 1000));
	Dispatcher = new btCollisionDispatcher(CollisionConfiguration);
	Solver = new btSequentialImpulseConstraintSolver();
	_world = new btDiscreteDynamicsWorld(
					Dispatcher,
					BroadPhase,
					Solver,
					CollisionConfiguration);
	_world->setGravity(btVector3(0,gravity,0));
}

void CPhysics::CleanUp()
{
	ClearObjects();
	delete _world;
	delete Solver;
	delete Dispatcher;
	delete BroadPhase;
	delete CollisionConfiguration;
}

void CPhysics::UpdatePhysics(u32 delta)
{
	// apply gravity
	for(auto it = _bodies.begin(); it != _bodies.end(); it++)
	{
		(*it)->applyGravity();
	}

	// simulate
	btScalar dlt = delta*0.001;
	_world->stepSimulation(dlt, 10, (1.f/30.f));

	// update irrlicht
	for(auto it = _bodies.begin(); it != _bodies.end(); it++)
	{
		UpdateRender(*it);
	}
}

void CPhysics::UpdateRender(btRigidBody* obj)
{
	scene::ISceneNode *node = static_cast<scene::ISceneNode*>(obj->getUserPointer());

	// set pos
	btVector3 point = obj->getCenterOfMassPosition();
	//std::cout << point[0] << ", " << point[1] << ", " << point[2] << std::endl;
    node->setPosition(core::vector3df((f32)point.getX(),(f32)point.getY(),(f32)point.getZ()));

	// set rot
	core::vector3df euler;
	const btQuaternion& quat = obj->getOrientation();
	core::quaternion q(quat.getX(),quat.getY(),quat.getZ(),quat.getW());
	q.toEuler(euler);
	euler *= core::RADTODEG;
	node->setRotation(euler);
}

void CPhysics::DeleteEntity(GOEntity* entity)
{
	auto it = std::remove(_bodies.begin(), _bodies.end(), entity->GetRigidBody());
	std::cout << "BEFORE: " << _bodies.size() << std::endl;
	_bodies.erase(it, _bodies.end());
	std::cout << "AFTAH: " << _bodies.size() << std::endl;
	btRigidBody* body = (*it);
	btCollisionObject* obj = static_cast<btCollisionObject*>(body);
	if(body && body->getMotionState())
	{
		delete body->getMotionState();
		delete body->getCollisionShape();
	}
	scene::ISceneNode *node = static_cast<scene::ISceneNode*>(body->getUserPointer());
	node->remove();
	_world->removeCollisionObject(obj);
	_world->removeRigidBody(body);
	delete obj;
}

void CPhysics::ClearObjects ()
{
	for(int i = _world->getNumCollisionObjects()-1; i>=0; i--)
	{
		btCollisionObject* obj = _world->getCollisionObjectArray()[i];
		btRigidBody* body = btRigidBody::upcast(obj);
		if(body && body->getMotionState())
		{
			delete body->getMotionState();
		}
		scene::ISceneNode *node = static_cast<scene::ISceneNode*>(body->getUserPointer());
		node->remove();
		_world->removeCollisionObject(obj);
		_world->removeRigidBody(body);
		delete obj;
	}

	_bodies.clear();
}

btRigidBody* CPhysics::PushObject(
		const btVector3& position,
		const core::vector3df& scale,
		btCollisionShape* colShape,
		btScalar mass)
{
	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(position);

	btDefaultMotionState *motionState =
		new btDefaultMotionState(transform);

	btVector3 localInertia(0,0,0);

	// dynamic!
	if(mass != 0.f)
		colShape->calculateLocalInertia(mass, localInertia);

	btRigidBody *rigidBody =
		new btRigidBody(mass, motionState, colShape, localInertia);
	_world->addRigidBody(rigidBody);
	_bodies.push_back(rigidBody);
	_shapes.push_back(colShape);

	return rigidBody;
}

void CPhysics::SetDebugDraw (CDebugDraw* debugDraw)
{
	_world->setDebugDrawer(debugDraw);
}

void CPhysics::DebugDrawWorld ()
{
	_world->debugDrawWorld();
}

btDiscreteDynamicsWorld* CPhysics::GetWorld()
{
	return _world;
}
