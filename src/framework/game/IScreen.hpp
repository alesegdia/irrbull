
#pragma once

#include "framework/game/IScreen.hpp"

class CGame;

class IScreen
{

public:
	IScreen() { };
	virtual ~IScreen() { };

	virtual void Init() {}
	virtual void Awake() {}
	virtual void Start() {}
	virtual void ConnectSlots() {}

	static CGame* game;

};

