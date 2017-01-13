#ifndef PARTICLEEMITTER_H
#define PARTICLEEMITTER_H
#include <map>
#include "Particle.h"
#define PI 3.14159
#define TO_RADIANS 1/180*PI

namespace Particles{
///Key for creating emitters (settings) easily
typedef struct{
    //Direction at which emitter points
    float direction = 0.f;
    //For how long do the particles live?
    sf::Time life = sf::seconds(1.f);
    //How wide is the range of the particles?
    float spread = 0.f;
    //What color are the particles?
    sf::Color color = sf::Color::White;
    //How many particles (per second) are being spawned?
    float PPS = 0.f;
    //What are the size of the particles?
    sf::Vector2f dimensions = sf::Vector2f(1.f,1.f);
    //How quickly are the particles moving?
    float speed = 0.f;
}EmitterKey;


class ParticleEmitter{
    public:
        ///CONSTRUCTORS
        ParticleEmitter(sf::Vector2f pos,float pps, float direction,
                        float speed,float spread, sf::Time life);
        ParticleEmitter(sf::Vector2f pos,EmitterKey &key);

        //Load emitter settings from an emitter key
        void loadFromKey(EmitterKey &key);

        void update();
        void emit(float ups = 60.f);
        void emit(sf::Time time,float ups = 60.f);
        void render(sf::RenderWindow *window);
//        bool collidingWith(Object *obj);
        virtual ~ParticleEmitter();
    public:
        void setPosition(float x,float y){_position = sf::Vector2f(x,y);_basePosition = _position;}
        void setPosition(sf::Vector2f pos){setPosition(pos.x,pos.y);}
        sf::Vector2f getPosition(){return _position;}
        void setLife(sf::Time life){_life = life;}
        void setColor(sf::Color color){_color = color;}
        void setDirection(float direction){_direction = direction;updateAngle();std::cout << _direction << std::endl;}
        void setPPS(float pps){_pps = pps;}
        void rotate(float angle,sf::Vector2f origin);
        void isCentered(bool center){_centered = center;}
    private:
        //When rotating -- or changing the emitter in any way that involves some
        //sort of change of direction/spread -- the emitter keeps its old rotation
        //properties, as the angleGen is only initialized automatically once
        //(at construction). Call this function whenever you change the rotation/spread
        //so that it can update accordingly
        void updateAngle(){
            if(!_centered){
                float centeredDirection = _direction/2.f;
                _angleGen.setMin(_direction+centeredDirection);
                _angleGen.setMax(_direction+centeredDirection+_spread);
            }else{
                _angleGen.setMin(_direction);_angleGen.setMax(_direction+_spread);
            }
        }
    private:
        //Position of the emitter
        sf::Vector2f _position;
        sf::Vector2f _basePosition;
        float _rotation = 0.f;
        //Direction of the emitter(where it is pointing; NOT
        //where all the pixels end up. It simply dictates where
        //the spread should start).
        float _direction = 0.f;
        //All particle objects
        std::vector<std::unique_ptr<Particle>> _particles;
        //Iterator for the current pixel
        std::vector<std::unique_ptr<Particle>>::iterator _current;
        Random<float> _angleGen = Random<float>(_direction,_direction+_spread);
    private:
        //Color of particles
        sf::Color _color = sf::Color::White;
        //Size of the particles
        sf::Vector2f _size;
        float _spread= 0.f;
        //Life of particles
        sf::Time _life = sf::Time::Zero;
        //Particles per second
        float _pps = 0.f;
        float _speed = 0.f;
        //Determines if the spread is justified at the center
        bool _centered = true;
        bool _emittingOnTimer = false;
        sf::Clock _emitClock;
        sf::Time _emitTime;
};
}

#endif // PARTICLEEMITTER_H
