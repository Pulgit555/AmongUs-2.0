#include "main.h"
#include "character.h"
#include "mirror.h"

#ifndef LIGHT_H
#define LIGHT_H


class Light {
public:
    Light() {}
    Light(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    double speed;
    double radius;
    int status;
    int d;
private:
    VAO *object;
};

#endif // light_H
