#ifndef MOUSEHOLDER_H
#define MOUSEHOLDER_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class MouseHolder{
    public:
        MouseHolder(sf::RenderWindow *window);
        sf::Vector2f getPosition();
    private:
        //Relative window
        sf::RenderWindow *_window = NULL;
};

#endif // MOUSEHOLDER_H
