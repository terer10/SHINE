#ifndef STATE_H
#define STATE_H
#include <SFML/Graphics.hpp>

class State{
    public:
        virtual void render(sf::RenderWindow *window){};
        virtual void update(sf::RenderWindow *window = NULL){};
        virtual void onCall(){};
        virtual void onStop(){};
};

#endif // STATE_H
