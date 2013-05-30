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

#include "CGameObjectManager.hpp"

CGameObjectManager::CGameObjectManager()
{

}

CGameObjectManager::~CGameObjectManager()
{

}

void CGameObjectManager::RegisterGameObject(IGameObject* go, const std::string& tag)
{
	_gameObjects.insert(std::make_pair(tag, go));
}

void CGameObjectManager::DeleteGameObjectById(const std::string& tag)
{
	// search on rigidbodies and delete rigidbody
	// unload gameobject
}

void CGameObjectManager::Awake()
{
	for(auto it = _gameObjects.begin(); it != _gameObjects.end(); ++it)
		(it->second)->Awake();
}

void CGameObjectManager::Start()
{
	for(auto it = _gameObjects.begin(); it != _gameObjects.end(); ++it)
		(it->second)->Start();
}

void CGameObjectManager::Update()
{
	for(auto it = _gameObjects.begin(); it != _gameObjects.end(); ++it)
		(it->second)->Update();
}

void CGameObjectManager::Unload()
{
	for(auto it = _gameObjects.begin(); it != _gameObjects.end(); ++it)
		(it->second)->Unload();
}
