#include "main.h"

#ifndef FUEL_H
#define FUEL_H


class Fuel {
public:
    Fuel() {}
    Fuel(float x, float y,float h ,color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object,*object1;
};

#endif // BALL_1