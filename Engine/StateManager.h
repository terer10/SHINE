#ifndef STATEMANAGER_H
#define STATEMANAGER_H
#include <iostream>
#include <memory>
#include <map>
#include <SFML/System.hpp>
#include "State.h"
//typedef std::pair<std::unique_ptr<State>,sf::Int16> StateKey;
class StateManager{
    public:
        virtual ~StateManager();

        void addState(std::unique_ptr<State>,sf::Int16 id,bool setActive = false);
        void removeState(int id);
        void setCurrentState(sf::Int16);
        void update(sf::RenderWindow *window = NULL);
        void render(sf::RenderWindow *window);
    protected:

    private:
        std::map<sf::Int16,std::unique_ptr<State>> _stateMap;
        State *_currentState = NULL;
};

#endif // STATEMANAGER_H
