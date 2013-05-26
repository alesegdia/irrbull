#ifndef __CENTITYCONTROLLER__
#define __CENTITYCONTROLLER__

#include "common.h"

class CEntityController : public IGameObject
{
public:
	CEntityController(CEngine* engine);
	~CEntityController();

	void AttachEntity(CEntity* entity);

	/* GAMEOBJECT INTERFACE */
	void Start();
	void Update();

private:
	CEngine* _engine;
	CEntity* _attachedEntity;
};


#endif
