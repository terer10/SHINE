#ifndef PLAYER_H
#define PLAYER_H

#include "Object.h"
#include "Controller.h"
typedef struct{
    sf::Vector2f position = sf::Vector2f(0.f,0.f);
    sf::Vector2f size = sf::Vector2f(0.f,0.f);
    sf::Vector2f scale = sf::Vector2f(1.f,1.f);

    //std::unique_ptr<sf::Texture> texture = make_unique<sf::Texture>();
    sf::Color color = sf::Color::White;

    float angle = 0.f;
    float alpha = 255.f;

    //Max movement speed(meters/second)
    float speed = 1.f;
    float meter = 0.f;
    sf::Vector2f gravity;
    float jumpHeight = 0.f;
    std::string id = "N/A";
}PlayerKey;
typedef struct{
    sf::Keyboard::Key left;
    sf::Keyboard::Key right;
    sf::Keyboard::Key jump;
}ControllerMap;

enum PlayerControls{
    Up,
    Down,
    Left,
    Right
};
class Player : public Object{
    public:
        Player(sf::Vector2f &pos,sf::Vector2f &siz,sf::Texture &texture,bool dynamic = false);
        Player(sf::Vector2f pos,sf::Vector2f siz, Controller controls, PlayerKey key, bool dynamic = true);
        void update(float dt);
        void updateCollision();
        void loadFromKey(PlayerKey key);
        virtual ~Player();
    private:
        void setupControls();
    private:
        void jump();
        void updateControls();
        void updateMovement();
        float _speed = 1.f;
        float _meter= 32.f;
        float _jumpHeight = 4.f;
        sf::Clock _runClock;
        bool _running = false;
        std::string _id = "player";
        Controller _controls;
};

#endif // PLAYER_H
