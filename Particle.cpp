#include "Particle.h"
using namespace Particles;
Particle::Particle(sf::Vector2f pos, sf::Vector2f size, float direction,float speed,sf::Color col){
    _position = pos;
    _size = size;
    _speed = speed;
    _direction = direction;
    _color = col;
    _body = make_unique<sf::RectangleShape>(_size);
    _body->setFillColor(_color);
    _body->setPosition(_position);
}
void Particle::update(){
    if(_body != NULL){
    _body->rotate(3.f);
    setAlpha(255.f/0.5f);
    //Move at the proper direction(angle) via trigonometry
    _body->move(std::cos(_direction*3.14/180)*_speed,std::sin(_direction*3.14/180)*_speed);
    }
}
void Particle::setAlpha(float alpha){
    _body->setFillColor(sf::Color(_color.r,_color.g,_color.b,alpha));
    _alpha = alpha;
}
void Particle::render(sf::RenderWindow *window){
    if(_body!=NULL)
    window->draw(*_body);
}
Particle::~Particle(){

}
