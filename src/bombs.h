#include "main.h"

#ifndef BOMBS_H
#define BOMBS_H


class Bombs {
public:
    Bombs() {}
    Bombs(float x, float y,float z ,color_t color);
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
