#include "MouseHolder.h"

MouseHolder::MouseHolder(sf::RenderWindow *window){
    _window = window;
}
sf::Vector2f MouseHolder::getPosition(){
    return static_cast<sf::Vector2f>(sf::Mouse::getPosition(*_window));
}

