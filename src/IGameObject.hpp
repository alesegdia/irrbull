#ifndef __IGAMEOBJECT__
#define __IGAMEOBJECT__

class IGameObject
{
public:
	virtual ~IGameObject()=0;
	virtual void Start();
	virtual void Update();
};

#endif
