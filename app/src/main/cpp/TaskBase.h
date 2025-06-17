#pragma once

class TaskSystem;
#include "framework.h"

class TaskBase
{
public:
	TaskBase() {}
	virtual ~TaskBase() = default;
	virtual void OnConstruct();
	virtual void OnDestruct();
	virtual void OnTick(float deltaTime);
	virtual void OnPostTick();
	virtual void OnDraw();
	virtual void OnPostDraw();
	virtual void OnCreate();
	virtual void OnDestroy();
	virtual void OnTouch(int action, int x, int y);
	virtual bool IsValid() const;
	virtual void EnsureWorld();
public:
	std::string name;
	TaskBase* parent = nullptr;
	int32_t id = 0;
	TaskSystem* ts = nullptr;
	int32_t tickPriority = 0;
	int32_t drawPriority = 0;
	mat4 localMatrix = mat4(1.0f);
	mat4 worldMatrix = mat4(1.0f);
	bool worldDirty = true;
	float elapsed = 0.0f;
	uint32_t tickCount = 0u;

};

