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

#include "GOEntityController.hpp"
#include "CEngine.hpp"
#include "GOEntity.hpp"
#include "GOCamera.hpp"
#include "CPhysics.hpp"

GOEntityController::GOEntityController()
{
}

GOEntityController::~GOEntityController()
{

}


void GOEntityController::AttachEntity(GOEntity* entity)
{
	_attachedEntity = entity;
}

void GOEntityController::AttachCamera(GOCamera* cam)
{
	_attachedCamera = cam;
}

void GOEntityController::Awake()
{
	_prevMouseXDelta = 0;
	_state = EState::IDLE;
}

void GOEntityController::Start()
{
	_attachedCamera->GetNode()->setParent(_attachedEntity->GetNode());
	_attachedCamera->GetNode()->setPosition(core::vector3df(-500,250,0));
}

void GOEntityController::Update()
{
	btRigidBody *rb = _attachedEntity->GetRigidBody();

	// state params
	EState prevState = _state;
	bool keyPress = false;

	// movement params
	f32 factor = 10.f;
	f32 damping = 0.9f;
	btVector3 sideStepLinearVel(0,0,0);
	btVector3 frontStepLinearVel(0,0,0);

	// ground raycast
	btVector3 start = rb->getCenterOfMassPosition();
	btVector3 end = start - btVector3(0,8,0);
	btCollisionWorld::ClosestRayResultCallback rayCallback(start, end);
	engine.GetPhysics()->GetWorld()->rayTest(start, end, rayCallback);

	// JUMP
	if(engine.IsKeyDown(irr::KEY_SPACE) && rayCallback.hasHit())
	{
		_attachedEntity->GetRigidBody()->activate(true);
		_attachedEntity->GetRigidBody()->clearForces();
		_attachedEntity->GetRigidBody()->setLinearVelocity(btVector3(0,0,0));
		_attachedEntity->GetRigidBody()->applyCentralForce(btVector3(0.f,30000.f,0.f));
	}

	// get forward
	btTransform xform;
	rb->getMotionState()->getWorldTransform(xform);
	btVector3 forward = xform.getBasis()[2];
	forward.normalize();

	// ROTATION
	// check this, maybe timing issues
	const s32 deltaMouseX = engine.GetEventReceiver()->mousePos.X - 100;
	//std::cout << "mousedeltax: " << deltaMouseX << std::endl;
	if(_prevMouseXDelta != deltaMouseX)
	{
		_prevMouseXDelta = deltaMouseX;
		engine.GetIrrDevice()->getCursorControl()->setPosition(100,100);
		rb->setAngularVelocity(btVector3(0,deltaMouseX*0.1,0));
	}
	// if(delta != lastDelta) do it! else idle...

	if(engine.IsKeyDown(irr::KEY_KEY_D))
	{
		sideStepLinearVel.setX( (forward.getX()) * factor);
		sideStepLinearVel.setY(0);
		sideStepLinearVel.setZ(-(forward.getZ()) * factor);
		keyPress = true;
	}
	else if(engine.IsKeyDown(irr::KEY_KEY_A))
	{
		sideStepLinearVel.setX(-(forward.getX()) * factor);
		sideStepLinearVel.setY(0);
		sideStepLinearVel.setZ( (forward.getZ()) * factor);
		keyPress = true;
	}

	// MOVEMENT
	if(engine.IsKeyDown(irr::KEY_KEY_W))
	{
		frontStepLinearVel.setX((forward.getZ()) * factor);
		frontStepLinearVel.setY(0);
		frontStepLinearVel.setZ((forward.getX()) * factor);
		keyPress = true;
	}
	else if (engine.IsKeyDown(irr::KEY_KEY_S))
	{
		frontStepLinearVel.setX(-(forward.getZ()) * factor);
		frontStepLinearVel.setY(0);
		frontStepLinearVel.setZ(-(forward.getX()) * factor);
		keyPress = true;
	}
	else
	{
		rb->setLinearVelocity(rb->getLinearVelocity() * btVector3(damping,1,damping));
	}

	_state = EState::IDLE;
	if(keyPress)
	{
		_state = EState::MOVING;
		rb->setLinearVelocity(
				btVector3(
					(frontStepLinearVel.getX() + sideStepLinearVel.getX()) * factor,
					rb->getLinearVelocity().getY(),
					(frontStepLinearVel.getZ() + sideStepLinearVel.getZ()) * factor));
	}

	if(!rayCallback.hasHit())
		_state = EState::JUMPING;

	scene::IAnimatedMeshSceneNode* node = _attachedEntity->GetNode();
	switch(_state)
	{
		case EState::IDLE:
			if(prevState != _state)
				node->setFrameLoop(22,22);
			break;

		case EState::JUMPING:
			if(prevState != _state)
				node->setFrameLoop(50,50);
			break;

		case EState::MOVING:
			if(prevState != _state)
				node->setFrameLoop(4,39);
			break;
	}

	btTransform xform2;
	_attachedEntity->GetRigidBody()->getMotionState()->getWorldTransform(xform2);
	btVector3 forward2 = xform2.getBasis()[2];
	forward2.normalize();
    _attachedCamera->LookAt(_attachedEntity->GetNode()->getPosition());
}

void GOEntityController::Unload()
{

}

