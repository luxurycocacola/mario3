#include "Physics.h"
#include <box2d.h>
#include <SFML/Graphics.hpp>

b2World* Physics::world{};
b2ContactListener* Physics::contactListener = nullptr;

class MyGlobalContactListener :
    public b2ContactListener
{
    // начло столкновения
    virtual void BeginContact(b2Contact* contact) override
    {   // получаем данные первого объекта
        FixtureData* data = (FixtureData*) contact->GetFixtureA()->GetUserData().pointer;

        if (data && data->listener) // проверка на получение данных и наличие в них слушателя(марио)
            data->listener->OnBeginContact(contact->GetFixtureA(), contact->GetFixtureB());

        // для второго объекта то же самое
        data = (FixtureData*) contact->GetFixtureB()->GetUserData().pointer;

        if (data && data->listener)
            data->listener->OnBeginContact(contact->GetFixtureB(), contact->GetFixtureA());
    }
    // конец столкновения
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

    if (!contactListener)
        contactListener = new MyGlobalContactListener(); // создаём один раз

    world->SetContactListener(contactListener);
}

void Physics::Update(float deltaTime)
{
    world->Step(deltaTime, 8, 3); // обновление физ. мира
}
