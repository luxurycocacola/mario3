#include "Coin.h"
#include "Resources.h"

#include<box2d.h>>

Coin::~Coin() {
	Physics::world->DestroyBody(body);
}

void Coin::Begin()
{
	tag = "coin";

	animation = Animation(1.4f,
		{
			AnimFrame(1.225f, Resources::textures["coin8.png"]),
			AnimFrame(1.05f,  Resources::textures["coin7.png"]),
			AnimFrame(0.875f, Resources::textures["coin6.png"]),
			AnimFrame(0.7f,   Resources::textures["coin5.png"]),
			AnimFrame(0.525f, Resources::textures["coin4.png"]),
			AnimFrame(0.35f,  Resources::textures["coin3.png"]),
			AnimFrame(0.175f, Resources::textures["coin2.png"]),
			AnimFrame(0.0f,   Resources::textures["coin1.png"]),
		});

	b2BodyDef bodyDef{};
	bodyDef.position.Set(position.x, position.y);
	b2Body* body = Physics::world->CreateBody(&bodyDef);
	b2PolygonShape shape{};
	shape.SetAsBox(0.4f, 0.4f);

	FixtureData* fixtureData = new FixtureData();
	fixtureData->type = FixtureDataType::Object;
	fixtureData->object = this;

	b2FixtureDef fixtureDef{};
	fixtureDef.userData.pointer = (uintptr_t)fixtureData;
	fixtureDef.isSensor = true;
	fixtureDef.density = 0.0f;
	fixtureDef.shape = &shape;
	body->CreateFixture(&fixtureDef);

}

void Coin::Update(float deltaTime)
{
	animation.Update(deltaTime);
}

void Coin::Render(Renderer& renderer)
{
	renderer.Draw(animation.GetTexture(), position, sf::Vector2f(0.8f, 0.8f));
}
