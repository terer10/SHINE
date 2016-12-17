#include "Controller.h"

Controller::Controller(){

}
bool Controller::isKeyPressed(KeyID key){
    //std::cout << key << std::endl;
    return sf::Keyboard::isKeyPressed(_keyMap[key]);
}
bool Controller::addKey(sf::Keyboard::Key key,KeyID id){
    //std::cout << key << std::endl;
    //Add key to map
    _keyMap.insert(std::make_pair(id,key));
    _keyState.insert(std::make_pair(id,state::none));
    //Throw exception if controller already has key
    ++_keyAmount;
}
void Controller::removeKey(KeyID key){
    _keyMap.erase(key);
    --_keyAmount;
}
