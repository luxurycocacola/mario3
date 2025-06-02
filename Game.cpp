#include "Game.h"
#include "Resources.h"
#include "Physics.h"
#include "Mario.h"
#include "Map.h"
#include <memory>
#include <filesystem>

Map map(1.0f);
Camera camera(20.0f);
std::vector<Object*> objects{};
bool paused{};

std::unique_ptr<Mario> mario;


sf::Image mapImage{};
sf::Font font{}; //шрифт
sf::Text coinsText("Coins", font);
sf::Text gameOverText("Text", font);
sf::Text restartHintText;
sf::RectangleShape backgroundShape(sf::Vector2f(1.0f, 1.0f));

void Restart() {

    Physics::Init();

    mario = std::make_unique<Mario>();

    mario->position = map.CreateFromImage(mapImage, objects);

    mario->isDead = false;
    paused = false;

    mario->Begin();

    for (auto& object : objects) {
        object->Begin();
    }
}

void Begin(const sf::Window& window) {
    // Загрузка текстур
    for (auto& file : std::filesystem::directory_iterator("./textures")) {
        if (file.is_regular_file() && file.path().extension() == ".png") {
            Resources::textures[file.path().filename().string()].loadFromFile(file.path().string());
        }
    }

    font.loadFromFile("font.ttf");

    coinsText.setFillColor(sf::Color::White);
    coinsText.setOutlineColor(sf::Color::Black);
    coinsText.setOutlineThickness(1.0f);
    coinsText.setScale(0.1f, 0.1f);

    gameOverText.setFont(font);
    gameOverText.setFillColor(sf::Color::White);
    gameOverText.setOutlineColor(sf::Color::Black);
    gameOverText.setOutlineThickness(1.0f);

    restartHintText.setFont(font);
    restartHintText.setFillColor(sf::Color::White);
    restartHintText.setOutlineColor(sf::Color::Black);
    restartHintText.setOutlineThickness(1.0f);

    backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
    backgroundShape.setOrigin(0.5f, 0.5f);

    mapImage.loadFromFile("map.png");

    Restart();
}

void Update(float deltaTime) {

    if (mario->isDead && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            Restart();

    if (mario->isDead || paused)
        return;

    Physics::Update(deltaTime);
    if (mario) mario->Update(deltaTime);

    camera.position = mario ? mario->position : camera.position;

    for (auto& object : objects) {
        object->Update(deltaTime);
    }
}

void Render(Renderer& renderer) {

    renderer.Draw(Resources::textures["sky.png"], camera.position, camera.GetViewSize());

    map.Draw(renderer);

    for (auto& object : objects) {
        object->Render(renderer);
    }
    if (mario) mario->Draw(renderer);

}

void RenderUI(Renderer& renderer)
{
    coinsText.setPosition(-camera.GetViewSize() / 2.0f + sf::Vector2f(2.0f, 1.0f));
    coinsText.setString("Coins " + std::to_string(mario->GetCoins()));
    renderer.target.draw(coinsText);

    if (paused || (mario && mario->isDead)) {
        sf::Vector2u windowSize = renderer.target.getSize();

        sf::View oldView = renderer.target.getView();

        sf::View uiView(sf::FloatRect(0, 0, (float)windowSize.x, (float)windowSize.y));
        uiView.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
        renderer.target.setView(uiView);

        // Затемнение
        backgroundShape.setSize(sf::Vector2f(windowSize.x, windowSize.y));
        backgroundShape.setOrigin(0.f, 0.f);
        backgroundShape.setPosition(0.f, 0.f);
        renderer.target.draw(backgroundShape);

        if (mario && mario->isDead) {
            gameOverText.setCharacterSize(48);
            gameOverText.setString("GAME OVER");
            sf::FloatRect goBounds = gameOverText.getLocalBounds();
            gameOverText.setOrigin(goBounds.width / 2.f, goBounds.height / 2.f);
            gameOverText.setPosition(windowSize.x / 2.f, windowSize.y / 2.f - 40.f);
            renderer.target.draw(gameOverText);

            restartHintText.setCharacterSize(24);
            restartHintText.setString("press the SPACE to start over");
            sf::FloatRect hintBounds = restartHintText.getLocalBounds();
            restartHintText.setOrigin(hintBounds.width / 2.f, hintBounds.height / 2.f);
            restartHintText.setPosition(windowSize.x / 2.f, windowSize.y / 2.f + 20.f);
            renderer.target.draw(restartHintText);
        }

        renderer.target.setView(oldView);
    }

}
   

void DeleteObject(Object* object) {

    const auto& it = std::find(objects.begin(), objects.end(), object);
    if (it != objects.end()) {
        delete* it;
        objects.erase(it); //удаление с экрана
    }
}
