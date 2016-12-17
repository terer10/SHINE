#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#include <iostream>
#include <memory>
#include <map>
template <class T>
class ResourceManager{
    public:
        ///GETTING A RESOURCE FOR USE
        T &get(int i){
            //Return reference to that item
            return *_resources[i];
        }
        ///LOADING A RESOURCE
        void load(const std::string &str,int i){
            std::unique_ptr<T> item = make_unique<T>();
            //If the item doesn't load for whatever reason,
            if(!item->loadFromFile(str)){
                //shut down the program
                throw std::runtime_error("Could not load " + str + ".");
            }
            //Add the item to the _resources map
            _resources.insert(std::make_pair(i,std::move(item)));
        };
    private:
        std::map<int,std::unique_ptr<T>> _resources;
};
typedef ResourceManager<sf::Texture> TextureManager;

#endif // RESOURCEMANAGER_H
