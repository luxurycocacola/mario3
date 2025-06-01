#pragma once
#include <SFML/Graphics.hpp>
#include "Renderer.h"
#include "Object.h"
#include "Camera.h"

extern Camera camera; // определяем камеру как внешнюю перемен. (чтобы исп в нескольких файлах
                      // и определить только в одном - в Game.cpp)
extern bool paused;

void Begin(const sf::Window& window);
void Update(float deltaTime);
void Render(Renderer& renderer);
void RenderUI(Renderer& renderer);

void DeleteObject(Object* object);
