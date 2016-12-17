#include "Player.h"

Player::Player(sf::Vector2f pos,sf::Vector2f siz, Controller controls,PlayerKey key,bool dynamic):Object(pos,siz,dynamic){
    _dynamic = dynamic;
    //Initialize object
    _body = make_unique<sf::RectangleShape>();
    _body->setPosition(pos);
    _body->setSize(siz);
    //Initialize texture
    _texture = make_unique<sf::Texture>();
    _gravity = sf::Vector2f(0,480);
    _controls = controls;
    //Configure controls
    setupControls();
    setID("player");
}
Player::Player(sf::Vector2f &pos,sf::Vector2f &siz,sf::Texture &texture,bool dynamic):Object(pos,siz,dynamic){}

void Player::setupControls(){
    _controls.addKey(sf::Keyboard::A,PlayerControls::Left);
    _controls.addKey(sf::Keyboard::D,PlayerControls::Right);
    _controls.addKey(sf::Keyboard::W,PlayerControls::Up);
    _controls.addKey(sf::Keyboard::S,PlayerControls::Down);
}
//Function to add controls
void Player::loadFromKey(PlayerKey key){
    setPosition(key.position);
    setSize(key.size);
    setScale(key.scale);

    //setTexture(key.texture);
    setColor(key.color);

    setAngle(key.angle);
    setAlpha(key.alpha);

    //Max movement speed(meters/second)
    _speed = key.speed;
    _meter = key.meter;
    _gravity = key.gravity;
    _jumpHeight = key.jumpHeight;
    _id = key.id;
}

void Player::jump(){

}
void Player::update(float dt){
    if(!_running){
        _runClock.restart();
    }
    updatePhysics(dt);
    updateCollision();
    //Update controls
    updateControls();
    project();
}

//Handle controls
void Player::updateControls(){
    //Move left
    if(_controls.isKeyPressed(PlayerControls::Left)){
        _velocity.x = -_speed*_runClock.getElapsedTime().asSeconds();
        _running = true;
    //Move right
    }else if(_controls.isKeyPressed((int)PlayerControls::Right)){
        _velocity.x = _speed*_runClock.getElapsedTime().asSeconds();
        _running = true;
    //Stay still
    }else{
        _velocity.x = 0;
        _running = false;
    }

    //Jumping
    if(_controls.isKeyPressed((int)PlayerControls::Up)){
        //Jump according to _jumpHeight
        if(_onGround){
            _velocity.y = -(_gravity.y+_jumpHeight);
        }
    }
    //Fall, x meters a second
    if(_velocity.y < 0.f){
        _velocity.y += 2.f;
    }
}

//Make sure collision works
void Player::updateCollision(){
    std::vector<Object*>::iterator objects;
    //Loop through all collidable objects(objects in _collidingObjects vector)
    for(objects = _collidingObjects.begin();objects != _collidingObjects.end();++objects){
        //If it is resting on one of these objects,
        if(collidingWith(SIDES::BOTTOM,(*objects))){
            //Set _onGround to true in order to inform the game that the player is on the ground
            _onGround = true;
            std::cout << "You're too...." << std::endl;
            //Keep the player resting on the object
            setGhostPosition(getPosition().x,(*objects)->getPosition().y-getBounds().height);
            //Break the loop so that it does not see an object that
            //the player is not colliding with and turn _onGround to false
            break;
        }else{
            //If the player isn't resting on anything, _onGround is set to false
            _onGround = false;
        }
    }
}

/*void Player::updateCollision(){
    std::vector<Object*>::iterator objects;
    sf::FloatRect ghostBox;
    for(objects = _collidingObjects.begin();objects != _collidingObjects.end();++objects){
        (*objects)->
    }
}*/
Player::~Player(){

}
