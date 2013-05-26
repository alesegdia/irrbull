#ifndef __CENTITY__
#define __CENTITY__

#include "common.h"

class CEntity : public IGameObject
{
public:
	CEntity();
	virtual ~CEntity();

	void Load(
			CEngine* engine,
			const std::string& meshPath,
			const std::string& texturePath,
			const btVector3& position=btVector3(0,0,0),
			const core::vector3df& scale=core::vector3df(1,1,1),
			btCollisionShape* shape=NULL,
			btScalar  mass=0);
	scene::IAnimatedMeshSceneNode* GetNode();
	void AttachCamera(scene::ICameraSceneNode* camNode,
			const core::vector3df& position);
	btRigidBody* GetRigidBody();

	/* GAMEOBJECT INTERFACE */
	void Start();
	void Update();

protected:
	scene::IAnimatedMesh *_mesh;
	scene::IAnimatedMeshSceneNode* _node;
	btRigidBody* _rigidBody;
};


#endif
