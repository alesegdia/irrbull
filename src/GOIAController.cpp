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

#include "GOIAController.hpp"
#include "GOEntity.hpp"

GOIAController::GOIAController()
{

}

GOIAController::~GOIAController()
{

}

void GOIAController::Awake()
{

}

void GOIAController::Start()
{

}

void GOIAController::Update()
{
    btRigidBody* plRb = _player->GetRigidBody();
    btRigidBody* myRb = _entity->GetRigidBody();

	// get forward
	btTransform xform;
	myRb->getMotionState()->getWorldTransform(xform);
	btVector3 forward = xform.getBasis()[2];
	forward.normalize();

    btScalar modulo = 30.f;
    btVector3 direccion = plRb->getCenterOfMassPosition() - myRb->getCenterOfMassPosition();
    direccion.normalize();
    f32 cos_angulo = direccion.dot(forward);
    f32 sin_angulo = sin(acos(cos_angulo));
    std::cout << "acos(" << cos_angulo << ") = " << acos(cos_angulo) * core::RADTODEG << std::endl;

	f32 delta = 0;
	f32 factor = 0.01f;
	myRb->activate(true);

	direccion *= modulo;
	myRb->setLinearVelocity(
			btVector3(
				direccion.getX(), myRb->getLinearVelocity().getY(), direccion.getZ()));
	//myRb->setAngularVelocity(
	//		btVector3(
	//			0.f, cos_angulo, 0.f));
}

void GOIAController::Unload()
{

}

void GOIAController::SetPlayer(GOEntity *player)
{
	_player = player;
}

void GOIAController::SetEntity(GOEntity *entity)
{
    _entity = entity;
}


