#pragma once
#include <iostream>
#include <vector>

namespace Components { enum ID; }

class Component
{
friend class Engine;

public:
	Component();
	~Component();

	virtual void Start() {} //= 0;
	virtual void Update(){} //= 0;
	virtual void Draw()	 {} //= 0;
	virtual void Stop()  {} //= 0;
	virtual void Kill()  {}
	virtual void OnResetDevice() {}
	virtual void OnLostDevice()  {}

	virtual void SetActive(bool toggle) { isActive = toggle; };

	//This is ugly, I'd rather not have strings though, find something else.
	void SetID(Components::ID id) { this->id = id; }
	const Components::ID GetID() { return id; }

protected:
	bool isActive;

private:
	// Components vectors
	static std::vector<Component*> components;
	static std::vector<Component*> toAdd;
	static std::vector<Component*> toDelete;
	static std::vector<Component*> removed;

	Components::ID id;
};

