#pragma once
#include <box2d.h>
#include "Renderer.h"

class Object;
class Mario;

class ContactListener {

public:
	virtual void OnBeginContact(b2Fixture* self, b2Fixture* other) = 0;
	virtual void OnEndContact(b2Fixture* self, b2Fixture* other) = 0;
};

enum class FixtureDataType
{
	Mario,
	MapTile,
	Object
};

struct FixtureData
{
	FixtureDataType type;
	ContactListener* listener;

	union
	{
		Mario* mario;
		Object* object;
		struct { int mapX, mapY; };
	};
};


class Physics
{
public:
	static b2ContactListener* contactListener;
	static void Init();
	static void Update(float deltaTime);

	static b2World* world;
};
