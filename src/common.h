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
#include <map>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include "IGameObject.hpp"
#include "TSingleton.hpp"

/* CORE OBJECTS */
class CGame;
class CPhysics;
class CEventReceiver;
class CEngine;
class CDebugDraw;
class CGameObjectManager;	// include header on hpp

/* GAME OBJECTS */
class GOEntity;
class GOEntityController;
class GOCamera;

/* NAMESPACES & ALIAS */
using namespace irr;

/* CONSTANTS */
const btScalar WORLD_GRAVITY = -100.f;

#endif
