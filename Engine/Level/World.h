#ifndef WORLD_H
#define WORLD_H

#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "make_unique.h"
#include "ResourceManager.h"
#include "State.h"
#include "Object.h"
#include "Object/Player.h"
#include "../Input/Controller.h"
typedef std::vector<std::unique_ptr<Object>>::iterator ObjectIterator;

class World : public State{
    public:
        World();
        void update(float dt);
        void render(sf::RenderWindow *window);
        void initObject();
        Object &addObject(sf::Vector2f pos,sf::Vector2f siz,bool dynamic = true);
        Object &addPlayer(sf::Vector2f pos,sf::Vector2f siz,Controller controls,bool dynamic);
        void setGravity(float grav);
       // virtual ~World();
    private:
        void updateCollision();
        std::unique_ptr<TextureManager> _textures;
        std::vector<std::unique_ptr<Object>> _objects;
        std::vector<std::unique_ptr<Player>> _players;
        std::map<Object*,bool> _objectCollisionMap;
        float _gravity = 1;
        float _gravityBuffer;
        unsigned int _objectAmount = 0;
        bool _hasObjects = false;
        ObjectKey key;
        PlayerKey _defaultPlayer;
        Controller _controller1;
        Controller _controller2;
};

#endif // WORLD_H
