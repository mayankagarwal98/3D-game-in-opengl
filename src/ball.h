#include "main.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(float x, float y, color_t color);
    glm::vec3 position;
    glm::mat4 rotation;
    float rotationx,rotationy,rotationz;
    glm::vec3 lo_x,lo_y,lo_z;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object,*object1;
};

#endif // BALL_1
