#include "Clickable.h"

//mouseButton: The mouse button that will be pressed to trigger click
bool Clickable::isClicked(unsigned int mouseButton){
    //If mouse is over object
    if(_boundingBox.contains(_mouseHolder->getPosition())){
        //and it is clicked
        if(sf::Mouse::isButtonPressed((sf::Mouse::Button)mouseButton)){
            //return true
            return true;
        }else{
            return false;
        }
    }
}

void Clickable::update(){

}
