#ifndef __CPHYSICS__
#define __CPHYSICS__

#include "common.h"

class CPhysics
{
public:
	CPhysics();
	~CPhysics();

	void Init(btScalar gravity);
	void UpdatePhysics (u32 delta);
	btRigidBody* PushObject(
			//scene::ISceneNode* node,
			const btVector3& position,
			const core::vector3df& scale,
			btCollisionShape* colShape = NULL,
			btScalar mass = 0.f);
	void ClearObjects();


private:
	void UpdateRender(btRigidBody* obj);

	boost::ptr_vector<btRigidBody> _bodies;

	/* Bullet stuff */
	btDiscreteDynamicsWorld* _world;
	btDefaultCollisionConfiguration *CollisionConfiguration;
	btBroadphaseInterface *BroadPhase;
	btCollisionDispatcher *Dispatcher;
	btSequentialImpulseConstraintSolver *Solver;
};

#endif
