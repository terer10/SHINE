#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include "make_unique.h"


enum SIDES{
    TOP,
    RIGHT,
    BOTTOM,
    LEFT
};

//ObjectKey is used to quickly make/mass-produce objects. These objects
//share characteristics such as color, alpha, scale, etc., with ObjectKey
typedef struct{
    public:
        sf::Vector2f position = sf::Vector2f(0.f,0.f);
        sf::Vector2f size = sf::Vector2f(0.f,0.f);
        sf::Vector2f scale = sf::Vector2f(1.f,1.f);

        std::unique_ptr<sf::Texture> texture = make_unique<sf::Texture>();
        sf::Color color = sf::Color::White;

        float angle = 0.f;
        float alpha = 255.f;
}ObjectKey;

class Object : public sf::Drawable{
    public:
        Object(sf::Vector2f pos,sf::Vector2f siz,bool dynamic = true);
        Object(sf::Vector2f &pos,sf::Vector2f &siz,sf::Texture &texture,bool dynamic = true);

        ///SCALE
        void setScale(float x,float y){_body->setScale(x,y);}
        void setScale(sf::Vector2f scale){_body->setScale(scale);}
        ///SIZE
        void setSize(sf::Vector2f siz){setScale(siz.x/_body->getGlobalBounds().width,siz.y/_body->getGlobalBounds().height);}
        void setSize(float x,float y){setSize(sf::Vector2f(x,y));}
        sf::Vector2f getSize(){return _body->getSize();}

        sf::Vector2f getPoint(unsigned int i){return _body->getPoint(i);}
        ///TEXTURE
        void setTexture(sf::Texture *texture){_body->setTexture(texture);}
        void setTexture(sf::Texture &texture){_body->setTexture(&texture);}
        void loadTexture(std::string &path);
        ///POSITION
        void setPosition(sf::Vector2f pos){_body->setPosition(pos);}
        void setPosition(float x,float y){_body->setPosition(sf::Vector2f(x,y));}
        void setGhostPosition(float x, float y){_ghostBox.top = x;_ghostBox.left = y;}
        sf::Vector2f getPosition(){return _body->getPosition();}
        //Set the object, by its center, at a certain point
        void setCenter(float x, float y);
        void setCenter(sf::Vector2f pos);
        //Move object
        void move(float x,float y){_body->move(x,y);}
        void move(sf::Vector2f mov){_body->move(mov);}

        void setID(std::string str){_id = str;}
        std::string getID(){return _id;}

        ///ANGLE
        void setAngle(float angle){_body->setRotation(angle);}
        void rotate(float a){_body->rotate(a);}
        ///COLOR
        void setColor(sf::Color &color){_body->setFillColor(color);}
        sf::Color getColor(){return _body->getFillColor();}
        void setAlpha(float alpha){_body->setFillColor(sf::Color(getColor().r,getColor().g,getColor().b,alpha));}
        //WARNING: BULKY
        void replaceColor(sf::Color &oldColor,sf::Color &newColor);

        //Move to certain area on screen
        void moveTo(sf::Vector2f &pos,sf::Vector2f &offset);
        void moveTo(sf::Vector2f &pos,float offset);

        sf::FloatRect getBounds(){return _body->getGlobalBounds();}
        bool intersecting(Object *object);
        bool contains(sf::Vector2f &pos);

        bool isDynamic(){return _dynamic;}
        void setDynamic(bool dyn){_dynamic = dyn;}

        bool collidingWith(SIDES side, Object *obj);
        void update(float dt);

        void setGravity(sf::Vector2f grav){_gravity = grav;}
        sf::Vector2f getGravity(){return _gravity;}

        void addCollidingObjects(Object *obj);
        void addCollidingObjects(std::vector<Object*> objects);

        void face(sf::Vector2f pos);

    protected:
        void project();
        bool _dynamic = true;
        void draw(sf::RenderTarget &target,sf::RenderStates states)const;
        void updatePhysics(float dt);
        std::unique_ptr<sf::Texture> _texture;
        std::unique_ptr<sf::RectangleShape> _body;
        sf::FloatRect _ghostBox;
        sf::Vector2f _gravity;
        sf::Clock _gravityTimer;
        bool _onGround = false;
        sf::Vector2f _velocity = sf::Vector2f(0.f,0.f);
        std::vector<Object*> _collidingObjects;
        std::string _id = "object";
        float _meter = 32.f;
};

#endif // OBJECT_H
