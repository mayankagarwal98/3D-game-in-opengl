#include "main.h"

#ifndef PARACHUTES_H
#define PARACHUTES_H


class Parachutes {
public:
    Parachutes() {}
    Parachutes(float x, float y,float z ,color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object;
};

#endif // BALL_1
