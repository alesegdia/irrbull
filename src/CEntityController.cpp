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

	std::cout << "ola q ase" << std::endl;
	std::cout << rb->getLinearVelocity().getY() << std::endl;

	// JUMP
	if(_engine->IsKeyDown(irr::KEY_SPACE) &&
		rb->getLinearVelocity().getY() < 0.01f)
	{
		std::cout << "cuentame lo q ase" << std::endl;
		//_attachedEntity->GetRigidBody()->applyCentralImpulse(btVector3(0.f,50.f,0.f));
		_attachedEntity->GetRigidBody()->activate(true);
		_attachedEntity->GetRigidBody()->applyCentralForce(btVector3(0.f,50000.f,0.f));
	}

	// ROTATION
	if(_engine->IsKeyDown(irr::KEY_KEY_D))
	{

	}

	// MOVEMENT
	if(_engine->IsKeyDown(irr::KEY_KEY_W))
	{
		btScalar xmov = rb->getOrientation().getX() * 2000;
		btScalar zmov = rb->getOrientation().getZ() * 2000;

		std::cout << "xmov: " << rb->getOrientation().getX()
			<< ", zmov: " << rb->getOrientation().getY() << std::endl;
		rb->activate(true);
		rb->setLinearVelocity(
				btVector3(xmov, rb->getLinearVelocity().getY(), zmov));
	}
}
