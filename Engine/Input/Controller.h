#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <iostream>
#include <exception>
#include <map>
#include <SFML/Window.hpp>

typedef int KeyID;
//Key already added
//std::exception key_added_error;

enum state{
    none,
    pressed,
    released,
    held
};

class Controller{
    public:
        Controller();
        //Check if key is pressed
        bool isKeyPressed(KeyID key);
        bool wasKeyReleased(KeyID key);
        //Add key
        bool addKey(sf::Keyboard::Key key,KeyID id);
        //Remove key
        void removeKey(KeyID key);
    protected:
        void updateState(KeyID key);
        std::map<KeyID,sf::Keyboard::Key> _keyMap;
        std::map<KeyID,state> _keyState;
        int _keyAmount = 0;
};

#endif // CONTROLLER_H
