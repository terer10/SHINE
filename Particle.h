#ifndef PARTICLE_H
#define PARTICLE_H
#include <memory>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "make_unique.h"
#include "Random.h"
namespace Particles{
class Particle{
    public:
        Particle(sf::Vector2f pos, sf::Vector2f size,float direction,float speed,sf::Color col);
        void update();
        void render(sf::RenderWindow *window);
        bool isAlive(){return _life.getElapsedTime() < _maxLife;}
        bool setTexture(sf::Texture *tex){_body->setTexture(tex);}
        void setColor(sf::Color col){_body->setFillColor(col); _color = col;}
        void setSpeed(float speed){_speed = speed;}
        void setAlpha(float alpha);
        float getAlpha(){return _alpha;}
        virtual ~Particle();
    private:
        //Position of the particle
        sf::Vector2f _position;
        //Size of the particle
        //float _size = 5.f;
        sf::Vector2f _size = sf::Vector2f(5.f,5.f);
        //Direction
        float _direction = 0.f;
        float _angle = 0.f;
        float _alpha = 255.f;
        float _speed = 5.f;
        sf::Color _color = sf::Color::White;
        sf::Clock _life;
        sf::Time _maxLife = sf::seconds(0.5f);
        std::unique_ptr<sf::RectangleShape> _body;
};
}
#endif // PARTICLE_H
