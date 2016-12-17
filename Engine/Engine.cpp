#include "Engine.h"

Engine::Engine(){
    _window = make_unique<sf::RenderWindow>(sf::VideoMode(640,480,32),"Days Are New");
    _world = make_unique<World>();
    _running = true;
    _world->setGravity(4.f);
    _body.setPosition(200,200);
    _body.setSize(sf::Vector2f(50,50));
    run();
}
void Engine::update(float dt){
    _world->update(dt);
}
void Engine::render(){
    _window->clear(sf::Color::Black);
    _world->render(_window.get());
    _window->draw(_body);
    _window->display();
}
void Engine::processEvents(){
    sf::Event e;
    while(_window->pollEvent(e)){
        if(e.type == sf::Event::Closed){
            _running = false;
            _window->close();
        }
    }
}
void Engine::run(){
    sf::Clock clock;
    const sf::Time UPDATE_TIME = sf::seconds(1.f/_ups);
    sf::Time dt;
    while(_running){
        dt = clock.getElapsedTime();
        processEvents();
        if(dt >= UPDATE_TIME){
            dt = UPDATE_TIME;
            update(UPDATE_TIME.asSeconds());
            clock.restart();
        }
        render();
    }
}
Engine::~Engine(){

}
