#ifndef __common__
#define __common__

/* COMMON LIBS */
#include <irrlicht/irrlicht.h>
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include <boost/ptr_container/ptr_vector.hpp>
#include <iostream>
#include <memory>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <cstring>

/* FORWARD DECLARING */
class CGame;
class CPhysics;
class CEventReceiver;
class CEngine;
class CEntity;

/* NAMESPACES & ALIAS */
using namespace irr;

/* CONSTANTS */
const btScalar WORLD_GRAVITY = -100.f;

#endif
