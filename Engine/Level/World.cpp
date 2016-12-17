#include "World.h"

World::World(){
    _textures = make_unique<TextureManager>();
    _textures->load("res/Page1.png",0);
/*    _controller1.jump = sf::Keyboard::W;
    _controller1.left = sf::Keyboard::A;
    _controller1.right = sf::Keyboard::D;

    _controller2.jump = sf::Keyboard::Up;
    _controller2.left = sf::Keyboard::Left;
    _controller2.right = sf::Keyboard::Right;*/

    addPlayer(sf::Vector2f(0,50),sf::Vector2f(32,32),_controller1,true);
    addPlayer(sf::Vector2f(0,50),sf::Vector2f(32,32),_controller2,true);
    addObject(sf::Vector2f(0,420),sf::Vector2f(500,20),false);
    addObject(sf::Vector2f(0,100),sf::Vector2f(500,20),true);
    addObject(sf::Vector2f(100,400),sf::Vector2f(200,20),false);
    initObject();
    //addObject(sf::Vector2f(450,0),sf::Vector2f(40,40),true);
}
void World::initObject(){
    for(unsigned int i = 0;i < _objectAmount;++i){
        _players[0]->addCollidingObjects(_objects[i].get());
    }
    _defaultPlayer.meter = 32;
    _defaultPlayer.speed = 20;
    _defaultPlayer.jumpHeight = 20;
    _defaultPlayer.gravity = sf::Vector2f(0,30);
    _defaultPlayer.size = sf::Vector2f(32,32);
    _defaultPlayer.color = sf::Color(200,60,30);
    _players[0]->loadFromKey(_defaultPlayer);
    _players[1]->loadFromKey(_defaultPlayer);
}
//Set global gravity of the world

void World::setGravity(float grav){
    _gravity = grav;
}

Object &World::addObject(sf::Vector2f pos,sf::Vector2f siz,bool dynamic){
    //Set the world to have objects if it's not set to it already
    if(!_hasObjects){
        _hasObjects = true;
    }
    //Add actual object
    _objects.push_back(make_unique<Object>(pos,siz,dynamic));
    //Add one to the object amount
    ++_objectAmount;
    //Return the object that was added
    return *_objects[_objectAmount];
}
Object &World::addPlayer(sf::Vector2f pos,sf::Vector2f siz, Controller controls,bool dynamic){
    _players.push_back(make_unique<Player>(pos,siz,controls,_defaultPlayer,dynamic));
    //Return the last player(the player that was just added)
    return *_players[_players.size()];
}
void World::render(sf::RenderWindow *window){
    //Check if there are any objects
    if(_hasObjects){
        //Draw all objects
        for(unsigned int i = 0;i < _objectAmount;++i){
            window->draw(*_objects[i]);
        }
        for(unsigned int i = 0;i < _players.size();++i){
            window->draw(*_players[i]);
        }
    }
}

void World::update(float dt){
    //Check if any objects are in the world
    if(_hasObjects){
        //Loop through objects
        for(unsigned int i = 0;i < _objectAmount;++i){
            //Is object dynamic(affected by physics)?
            if(_objects[i]->isDynamic()){
                //If so, update those physics!
                _objects[i]->update(dt);
            }
        }
        //Update the player
        for(unsigned int i = 0;i < _players.size();++i){
            _players[i]->update(dt);
        }
    //if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
//        updateCollision();
    }
}
/*void World::updateCollision(){
    //New bounding box to predict where the next box will be
    sf::FloatRect ghostBounds;
    //Iterators
    ObjectIterator obj1;
    ObjectIterator obj2;
    //Loop through objects
    for(obj1 = _objects.begin();obj1 != _objects.end();++obj1){
        for(obj2 = _objects.begin();obj2 != _objects.end();++obj2){
            //Make sure it's not checking for colliding itself
            if((obj1) != (obj2)){
                //Are the objects intersecting?
                if((*obj1)->collidingWith(SIDES::BOTTOM,(*obj2).get())){
                    (*obj1)->setPosition((*obj1)->getPosition().x,(*obj2)->getPosition().y - (*obj1)->getSize().y);
                }
            }
        }
        _players[0]->updateCollision((*obj1).get());
    }
}*/
