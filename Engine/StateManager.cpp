#include "StateManager.h"

void StateManager::addState(std::unique_ptr<State> state,sf::Int16 id,bool setActive){
    _stateMap.insert(std::make_pair(id,std::move(state)));
    if(setActive){
        setCurrentState(id);
    }
}
void StateManager::removeState(int id){
    _stateMap[id].reset();
    _stateMap.erase(id);
}
void StateManager::setCurrentState(sf::Int16 id){
    _currentState = _stateMap[id].get();
}
void StateManager::update(sf::RenderWindow *window){
    _currentState->update(window);
}
void StateManager::render(sf::RenderWindow *window){
    _currentState->render(window);
}
