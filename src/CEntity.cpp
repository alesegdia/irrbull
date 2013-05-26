#include "CEntity.hpp"
#include "CEngine.hpp"
#include "CPhysics.hpp"

CEntity::CEntity()
{

}

CEntity::~CEntity()
{

}

void CEntity::Load(CEngine* engine, const std::string& meshPath,
		const std::string& texturePath, const btVector3& position,
		const core::vector3df& scale, btCollisionShape* colShape, btScalar mass)
{
	_mesh = engine->GetSMgr()->getMesh(meshPath.c_str());

	if(!_mesh)
		exit(EXIT_FAILURE);

	video::IVideoDriver* driver = engine->GetVideoDriver();

	_node = engine->GetSMgr()->addAnimatedMeshSceneNode(_mesh);
	_node->setMaterialFlag(irr::video::EMF_LIGHTING, true);

	if(texturePath != "")
		_node->setMaterialTexture(0, driver->getTexture(texturePath.c_str()));

	_node->setScale(scale);

	_rigidBody = engine->GetPhysics()->PushObject(position, scale, colShape, mass);
	_rigidBody->setUserPointer((void*)(_node));
}

scene::IAnimatedMeshSceneNode* CEntity::GetNode()
{
	return _node;
}

btRigidBody* CEntity::GetRigidBody()
{
	return _rigidBody;
}

void CEntity::AttachCamera(scene::ICameraSceneNode* camNode, const core::vector3df& position)
{
	camNode->setParent(_node);
	camNode->setPosition(position);
}
