#include "main.h"

#ifndef FUELUP_H
#define FUELUP_H


class Fuelup {
public:
    Fuelup() {}
    Fuelup(float x, float y,float h ,color_t color);
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
