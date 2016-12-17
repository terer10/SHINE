#ifndef CLICKABLE_H
#define CLICKABLE_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "../MouseHolder.h"
enum State{
    Pressed,
    Clicked,
    Hovered,
    None
};
class Clickable{
    public:
        bool isPressed();
        bool isClicked(unsigned int i = 0);
    protected:
        void update();
        sf::FloatRect _boundingBox;
        MouseHolder *_mouseHolder = NULL;

};


#endif // CLICKABLE_H
