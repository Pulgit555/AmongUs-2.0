#include "main.h"
#include "character.h"
#include "mirror.h"

#ifndef COIN_DESIGN_H
#define COIN_DESIGN_H


class Coin_design {
public:
    Coin_design() {}
    Coin_design(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void set_value(int z);
    void tick();
    double speed;
    double radius;
    int status;
    int d;
private:
    VAO *object;
};

#endif // Coin_design_H
