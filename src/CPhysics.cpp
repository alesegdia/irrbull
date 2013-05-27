#include "CPhysics.hpp"
#include "CDebugDraw.hpp"

CPhysics::CPhysics()
{

}

CPhysics::~CPhysics()
{
	delete _world;
	delete Solver;
	delete Dispatcher;
	delete BroadPhase;
	delete CollisionConfiguration;
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

void CPhysics::UpdatePhysics(u32 delta)
{
	// apply gravity

	for(auto it = _bodies.begin(); it != _bodies.end(); it++)
	{
		(*it).applyGravity();
	}

	// simulate
	btScalar dlt = delta*0.001;
	_world->stepSimulation(dlt, 60);

	// update irrlicht
	for(auto it = _bodies.begin(); it != _bodies.end(); it++)
	{
		UpdateRender(&(*it));
	}
}

void CPhysics::UpdateRender(btRigidBody* obj)
{
	scene::ISceneNode *node = static_cast<scene::ISceneNode*>(obj->getUserPointer());

	// set pos
	btVector3 point = obj->getCenterOfMassPosition();
	node->setPosition(core::vector3df((f32)point[0],(f32)point[1],(f32)point[2]));

	// set rot
	core::vector3df euler;
	const btQuaternion& quat = obj->getOrientation();
	core::quaternion q(quat.getX(),quat.getY(),quat.getZ(),quat.getW());
	q.toEuler(euler);
	euler *= core::RADTODEG;
	node->setRotation(euler);
}

void CPhysics::ClearObjects ()
{
	for(auto it = _bodies.begin(); it != _bodies.end(); it++)
	{
		btRigidBody obj = *it;
		scene::ISceneNode *node = static_cast<scene::ISceneNode*>(obj.getUserPointer());
		node->remove();
		_world->removeRigidBody(&obj);
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
