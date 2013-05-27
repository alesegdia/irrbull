#include "CEntityController.hpp"
#include "CEntity.hpp"
#include "CEngine.hpp"

CEntityController::CEntityController(CEngine* engine)
{
	_engine = engine;
}

CEntityController::~CEntityController()
{

}

void CEntityController::AttachEntity(CEntity* entity)
{
	_attachedEntity = entity;
}

void CEntityController::Start()
{

}

void CEntityController::Update()
{
	btRigidBody *rb = _attachedEntity->GetRigidBody();

	// JUMP
	if(_engine->IsKeyDown(irr::KEY_SPACE) &&
		rb->getLinearVelocity().getY() < 0.01f)
	{
		_attachedEntity->GetRigidBody()->activate(true);
		_attachedEntity->GetRigidBody()->applyCentralForce(btVector3(0.f,50000.f,0.f));
	}

	// get forward
	btTransform xform;
	rb->getMotionState()->getWorldTransform(xform);
	btVector3 forward = xform.getBasis()[2];
	forward.normalize();

	// ROTATION
	// check this, maybe timing issues
	const s32 deltaMouseX = _engine->GetEventReceiver()->mousePos.X - 100;
	// if(delta != lastDelta) do it! else idle...
	_engine->GetIrrDevice()->getCursorControl()->setPosition(100,100);
	rb->setAngularVelocity(btVector3(0,deltaMouseX*0.1,0));
	/*  
	if(_engine->IsKeyDown(irr::KEY_KEY_D))
	{
		rb->activate(true);
		rb->setAngularVelocity(btVector3(0,deltaMouseX,0));
		//rb->applyTorque(btVector3(0,100,0));
	}
	else if(_engine->IsKeyDown(irr::KEY_KEY_A))
	{
		rb->activate(true);
		rb->setAngularVelocity(btVector3(0,-1,0));
		//rb->applyTorque(btVector3(-100,-100,0));
	}
	else
	{
		rb->setAngularVelocity(btVector3(0,0,0));
	}
	*/

	std::cout << rb->getOrientation().getAngle() * core::RADTODEG << std::endl
		<< rb->getOrientation().getW() << std::endl;

	// MOVEMENT
	if(_engine->IsKeyDown(irr::KEY_KEY_W))
	{
		f32 factor = 30.f;

		rb->activate(true);
		rb->setLinearVelocity(
				btVector3(
					(forward.getZ()) * factor,
					rb->getLinearVelocity().getY(),
					(forward.getX()) * factor));
	}
	else
	{
		//setLinearVelocity(0)? setDamping(?)?
	}
}
