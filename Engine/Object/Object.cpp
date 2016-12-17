#include "Object.h"

Object::Object(sf::Vector2f pos,sf::Vector2f siz,bool dynamic){
    _dynamic = dynamic;
    //Initialize object
    _body = make_unique<sf::RectangleShape>();
    _body->setPosition(pos);
    _body->setSize(siz);
    //Initialize texture
    _texture = make_unique<sf::Texture>();
    std::cout << pos.x << " | " << pos.y << std::endl;
    _ghostBox = sf::FloatRect(pos.x,pos.y,siz.x,siz.y);
}
Object::Object(sf::Vector2f &pos,sf::Vector2f &siz,sf::Texture &texture,bool dynamic){
    _dynamic = dynamic;
    //Initialize object
    _body = make_unique<sf::RectangleShape>();
    _body->setPosition(pos);
    _body->setSize(siz);
    //Initialize texture
    _texture = make_unique<sf::Texture>();
    _body->setTexture(&texture);
}
void Object::draw(sf::RenderTarget &target, sf::RenderStates states)const{
    target.draw(*_body,states);
}

//BULKY
void Object::replaceColor(sf::Color &oldColor,sf::Color &newColor){
    //Loop through all x-y pixel position
    //Convert the texture into an image
    sf::Image img = _body->getTexture()->copyToImage();
    //Create temporary texture
    sf::Texture texture;
    //Loop through every pixel in the image
    for(unsigned int x = 0;x <_body->getSize().x;++x){
        for(unsigned int y = 0;y <_body->getSize().y;++y){
            //If the current pixel-color is oldColor
            if(img.getPixel(x,y) == oldColor){
                //Turn that pixel into a newColor-colored pixel
                img.setPixel(x,y,newColor);
            }
        }
    }
    //Convert the image into a texture, via temporary texture
    texture.loadFromImage(img);
    //Set the current texture to the temporary texture
    setTexture(texture);
}
void Object::loadTexture(std::string &path){
    sf::Texture tex;
    tex.loadFromFile(path);
    _body->setTexture(&tex);
}

//MOVE TO POINT
void Object::moveTo(sf::Vector2f &pos,float offset){
    if(getPosition().x != pos.x){
        if(getPosition().x > pos.x){
            move(offset,0);
        }
    }
}

bool Object::intersecting(Object *object){
    if(getBounds().intersects(object->getBounds()))
        return true;
    else
        return false;
}
bool Object::contains(sf::Vector2f &pos){
    return getBounds().contains(pos);
}

//MOVE CENTER
void Object::setCenter(float x, float y){
    _body->setPosition(x - (_body->getSize().x/2),y - (_body->getSize().y));
}
void Object::setCenter(sf::Vector2f pos){
    _body->setPosition(pos.x - _body->getSize().x,pos.y - _body->getSize().y);
}

bool Object::collidingWith(SIDES side,Object *obj){
    if(_ghostBox.intersects(obj->getBounds())){
        switch(side){
        case SIDES::TOP:
            if(_velocity.y < 0 || _gravity.y < 0){
                return true;
            }else{
                return false;
            }
            break;
        //If the bottom side of the object is colliding with something,
        case SIDES::BOTTOM:
            //And the object was just going down
            if(_velocity.y > 0 || _gravity.y > 0){
                return true;
            }else{
                return false;
            }
            break;
        }
    }
}

void Object::addCollidingObjects(Object* obj){
    _collidingObjects.push_back(obj);
}
void Object::addCollidingObjects(std::vector<Object*> obj){
    for(int i = 0;i < obj.size();++i){
        _collidingObjects.push_back(obj[i]);
    }
}

//PHYSICS
void Object::updatePhysics(float dt){
    static const float MPS = _meter*dt;
    //Regulate velocity
    //Update the gravity if in the air
    if(!_onGround && _dynamic){
        _ghostBox.top += (_velocity.y + _gravity.y)*MPS;
        //_ghostBox.width += (_velocity.y + _gravity.y)*MPS;
    }else{
        //_ghostBox.top += (_velocity.y + _gravity.y)*MPS;
        //_ghostBox.width += (_velocity.y + _gravity.y)*MPS;
    }
}
void Object::update(float dt){
    updatePhysics(dt);
    project();
}
//Set the box to have the same position as the projection/pr
void Object::project(){
    setPosition(_ghostBox.left,_ghostBox.top);
    //setSize(_ghostBox.width,_ghostBox.height);
}
