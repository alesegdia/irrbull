#ifndef __CCHARACTER__
#define __CCHARACTER__

#include "common.h"
#include "CEntity.hpp"

class CPlayer : public CEntity
{
public:
	CPlayer();
	~CPlayer();

	void Load();
	// override CEntity::Update
	void Update();
}

#endif
