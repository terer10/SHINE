#ifndef ENGINE_H
#define ENGINE_H
#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include "World.h"
#include "make_unique.h"
#define TO_RADIANS 0.0174533

class Engine{
    public:
        Engine();
        virtual ~Engine();
    private:
        void update(float dt);
        void render();
        void processEvents();
        void run();
        std::unique_ptr<World> _world;
        std::unique_ptr<sf::RenderWindow> _window;
        const int _ups = 60.f;
        sf::Clock _globalClock;
        sf::Time _deltaTime = sf::Time::Zero;
        bool _running = false;
        sf::RectangleShape _body;

};

#endif // ENGINE_H
