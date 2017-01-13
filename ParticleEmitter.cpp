#include "ParticleEmitter.h"
using namespace Particles;
ParticleEmitter::ParticleEmitter(sf::Vector2f pos,float pps,float direction,
                                 float speed, float spread,sf::Time life){
    _position = pos;
    _pps = pps;
    _direction = direction;
    _speed = speed;
    _spread = spread;
    _life = life;
}
ParticleEmitter::ParticleEmitter(sf::Vector2f pos,EmitterKey &key){
    //Set position of the
    _position = pos;
    loadFromKey(key);
    _angleGen = Random<float>(_direction,_direction+_spread);
}

void ParticleEmitter::loadFromKey(EmitterKey &key){
    _direction = key.direction;
    _life = key.life;
    _spread = key.spread;
    _color = key.color;
    _pps = key.PPS;
    _speed = key.speed;
    _size = key.dimensions;
}

void ParticleEmitter::update(){
    std::cout << _emitClock.getElapsedTime().asSeconds() << std::endl;
    //If there are particles in the vector,
    if(!_particles.empty()){
        //Loop through all of them,
        for(int i = 0;i < _particles.size();++i){
            //and if the current one is not NULL,
            if(_particles[i] != nullptr){
                //, and it's still alive,
                if(_particles[i]->isAlive()){
                    //update it.
                    _particles[i]->update();
                }else{
                    //If it's not still alive, erase it.
                    _particles.erase(_particles.begin() + i);
                }
            }
        }
    }
    if(_emittingOnTimer && _emitClock.getElapsedTime() < _emitTime){
        emit();
    }
}
void ParticleEmitter::render(sf::RenderWindow *window){
    if(!_particles.empty()){
        for(_current = _particles.begin();_current != _particles.end();++_current){
            if((*_current) != NULL)
            (*_current)->render(window);
        }
    }
}
void ParticleEmitter::emit(float ups){
    //Divide pps(particles-per-second) by ups(updates per second) to push out
    //the exact amount of particles needed by the emitter
    for(float i = 0.f;i < _pps/ups;++i){
        _particles.push_back(make_unique<Particle>(_position,sf::Vector2f(_size.x,_size.y),_angleGen.next(),_speed,_color));
    }
}

void ParticleEmitter::emit(sf::Time time,float ups){
    if(_emittingOnTimer == false){
        _emitClock.restart();
    }
    _emittingOnTimer = true;
    _emitTime = time;
}
void ParticleEmitter::rotate(float angle,sf::Vector2f origin){
    //Rotation formula:
    //'x = cos(ang)*x - sin(ang)*y
    //'y = cos(ang)*y + sin(ang)*x
    float x = std::cos(angle*TO_RADIANS)*origin.x - std::sin(angle*TO_RADIANS)*origin.y;
    float y = std::cos(angle*TO_RADIANS)*origin.y + std::sin(angle*TO_RADIANS)*origin.x;
    setPosition(sf::Vector2f(x,y));
    _rotation = fmod(angle,360.f);
}
ParticleEmitter::~ParticleEmitter(){

}
