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

#ifndef __CGAMEOBJECTMANAGER__
#define __CGAMEOBJECTMANAGER__

#include "common.h"

class CGameObjectManager
{
public:
	CGameObjectManager();
	~CGameObjectManager();

	// another param <bool> updatable?
	// 2 lists, 1 updatable other nothing
	void RegisterGameObject(IGameObject* go, const std::string& tag);
	void DeleteGameObjectById(const std::string& tag);

	void Awake();
	void Start();
	void Update();
	void Unload();
	void FreeEverything();
	void SetEngine(CEngine *engine)
	{
		_engine = engine;
	}

	template<class T>
	T* GetGameObjectByTag(const std::string& tag)
	{
		return (static_cast<T*>(_gameObjects[tag]));
	}

private:
	std::map<std::string, IGameObject*> _gameObjects;
	CEngine* _engine;
};

#endif
