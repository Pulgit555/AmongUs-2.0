#include "main.h"
#include "character.h"
#include "mirror.h"

#ifndef BOMB_H
#define BOMB_H


class Bomb {
public:
    Bomb() {}
    Bomb(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void set_value(int z);
    void tick();
    int collision(Character character,Mirror mirror);
    double speed;
    double radius;
    int status;
    int d;
private:
    VAO *object;
};

#endif // bomb_H
