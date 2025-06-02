#include "Physics.h"
#include <box2d.h>
#include <SFML/Graphics.hpp>

b2World* Physics::world{};


class MyGlobalContactListener :
    public b2ContactListener
{
    virtual void BeginContact(b2Contact* contact) override
    {
        FixtureData* data = (FixtureData*) contact->GetFixtureA()->GetUserData().pointer;

        if (data && data->listener)
            data->listener->OnBeginContact(contact->GetFixtureA(), contact->GetFixtureB());

        data = (FixtureData*) contact->GetFixtureB()->GetUserData().pointer;

        if (data && data->listener)
            data->listener->OnBeginContact(contact->GetFixtureB(), contact->GetFixtureA());
    }
    
    virtual void EndContact(b2Contact* contact) override
    {
        FixtureData* data = (FixtureData*) contact->GetFixtureA()->GetUserData().pointer;

        if (data && data->listener)
            data->listener->OnEndContact(contact->GetFixtureA(), contact->GetFixtureB());

        data = (FixtureData*) contact->GetFixtureB()->GetUserData().pointer;

        if (data && data->listener)
            data->listener->OnEndContact(contact->GetFixtureB(), contact->GetFixtureA());
    }
};

void Physics::Init()
{   
    if (world)
        delete world;

    world = new b2World(b2Vec2(0.0f, 9.2f));
}

void Physics::Update(float deltaTime)
{
    world->Step(deltaTime, 8, 3);
    world->SetContactListener(new MyGlobalContactListener());
}
