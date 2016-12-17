#ifndef LEVEL_H
#define LEVEL_H
#include "../Object/Object.h"

class Level{
    public:
        Level();

        virtual ~Level();
    private:
        std::unique_ptr<Object> _walls;
};

#endif // LEVEL_H
