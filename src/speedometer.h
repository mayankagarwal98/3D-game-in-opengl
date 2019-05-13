#include "main.h"

#ifndef SPEEDOMETER_H
#define SPEEDOMETER_H


class Speedometer {
public:
    Speedometer() {}
    Speedometer(float x, float y,float theta ,color_t color);
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
