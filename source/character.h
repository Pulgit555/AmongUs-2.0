#include "main.h"

#ifndef CHARACTER_H
#define CHARACTER_H


class Character {
public:
    Character() {}
    Character(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void set_value(int z);
    void change_hel(int x);
    void tick();
    double speed;
    double radius;
    int health;
    int powerup;
    int d;
private:
    VAO *object;
};

#endif // Character_H
